#include "ft_nm.h"

static void        print_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	uint32_t		nsyms;

    i = 0;
	nsyms = swap32_if(file->symtab_cmd->nsyms, file->endian);
    while (i < nsyms)
    {
		if (file->symbols[i].type == '-')
		{
			i++;
			continue ;
		}
        if (file->symbols[i].type != 'U' && file->symbols[i].type != 'u')
		    ft_puthexa(file->symbols[i].value);
        else
            write(1, "                ", 16);
        write(1, " ", 1);
		ft_putchar(file->symbols[i].type);
        write(1, " ", 1);
		ft_putendl(file->symbols[i].name);
        i++;
    }
}

static t_ex_ret		fill_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	struct nlist_64	*nlist;
	char			*stringtable;
	void			*check;
	uint32_t		nsyms;

	nsyms = swap32_if(file->symtab_cmd->nsyms, file->endian);
		// ft_putendl("fill_symbols_table begin");
	nlist = (struct nlist_64 *)(file->ptr \
		+ swap32_if(file->symtab_cmd->symoff, file->endian));
	check = is_in_file(file, nlist, sizeof(*nlist) * nsyms);
	stringtable = (char *)is_in_file(file, (file->ptr \
		+ file->symtab_cmd->stroff), sizeof(*stringtable));
	if (!check || !stringtable)
        return (put_error(file->filename, VALID_OBJECT));
	i = 0;
	while (i < nsyms)
	{
		// ft_putendl("fill_symbols_table while");
		file->symbols[i].value = swap64_if(nlist[i].n_value, file->endian);
        file->symbols[i].name = (char *)is_in_file(file, \
			stringtable + swap32_if(nlist[i].n_un.n_strx, file->endian), \
			sizeof(*file->symbols[i].name));
		if (!file->symbols[i].name)
			file->symbols[i].name = BAD_STRING_INDEX;
		file->symbols[i].type = get_type_char(nlist[i].n_type, \
			nlist[i].n_sect, nlist[i].n_value, file);
        i++;
	}
		// ft_putendl("fill_symbols_table end");

	return (SUCCESS);
}

static t_ex_ret			get_sections_indices_64(t_bin_file *file, \
							struct segment_command_64 *segment, uint8_t nb_sect)
{
	uint32_t 					i;
	size_t						size_sections;
	struct section_64			*section;
	void						*check;
	uint32_t					nsects;

	nsects = swap32_if(segment->nsects, file->endian);
	section = (struct section_64 *)is_in_file(file, ((void *)segment \
		+ sizeof(struct segment_command_64)), sizeof(*section));
	size_sections = nsects * sizeof(*section);
	if (!section || !(check = is_in_file(file, section, size_sections)))
        return (put_error(file->filename, VALID_OBJECT));
	i = 0;
	while (i < nsects)
	{
		// ft_putendl("get_sections_indices while");
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = i + nb_sect;
		section = (void *)section + sizeof(struct section_64);
		i++;
	}
		// ft_putendl("get_sections_indices end");
    return (SUCCESS);
}

static t_ex_ret			init_file_64(t_bin_file *file)
{
	struct mach_header_64	        *header;
	struct load_command		        *lc;
	struct segment_command_64	    *segment;
	uint32_t					    i;
	uint8_t					        nb_sect;

    header = (struct mach_header_64 *)is_in_file(file, file->ptr, \
		sizeof(*header));
    if (!header)
        return (put_error(file->filename, VALID_OBJECT));
    lc = (struct load_command *)is_in_file(file, file->ptr + sizeof(*header), \
		sizeof(*lc));
    if (!lc)
        return (put_error(file->filename, VALID_OBJECT));
	i = 0;
	nb_sect = 1;
	while (i < swap32_if(header->ncmds, file->endian))
	{
		// ft_putendl("init_file while");
		if (lc->cmd == LC_SYMTAB)
        {
			file->symtab_cmd = (struct symtab_command *)is_in_file(file, lc, \
				sizeof(*(file->symtab_cmd)));
			if (!file->symtab_cmd)
                return (put_error(file->filename, VALID_OBJECT));
        }
		else if (lc->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)is_in_file(file, lc, \
				sizeof(*segment));
			if (!segment)
                return (put_error(file->filename, VALID_OBJECT));
			if (get_sections_indices_64(file, segment, nb_sect) == FAILURE)
                return (FAILURE);
			nb_sect += swap32_if(segment->nsects, file->endian);
		}
        i++;
		if ((swap32_if(lc->cmdsize, file->endian) % 8) != 0)
            return (put_error(file->filename, VALID_OBJECT));
		lc = (struct load_command *)is_in_file(file, (void *)lc \
			+ swap32_if(lc->cmdsize, file->endian), sizeof(*lc));
		if (!lc)
            return (put_error(file->filename, VALID_OBJECT));
	}
	// ft_putendl("init_file end");
    return (SUCCESS);
}

t_ex_ret	        handle_magic_64(char *filename, t_endian endian, \
						size_t size, void *ptr)
{
	t_bin_file		        file;

    ft_bzero(&file, sizeof(file));
    file.filename = filename;
	file.endian = endian;
	file.ptr = ptr;
	file.size = size;
	file.end = ptr + size;
    if (init_file_64(&file) == FAILURE)
        return (FAILURE);
	if (!file.symtab_cmd)
		return (FAILURE);
    file.symbols = (t_symbol*)ft_memalloc(sizeof(t_symbol) \
		* file.symtab_cmd->nsyms);
    if (!file.symbols)
		return (FAILURE);
	if (fill_symbols_table_64(&file) == FAILURE)
		return (FAILURE);
    if (sort_symbols(&file) == FAILURE)
		return (FAILURE);
	print_symbols_table_64(&file);
	free(file.symbols);
	return (SUCCESS);
}
