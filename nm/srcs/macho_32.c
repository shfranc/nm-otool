#include "ft_nm.h"

static void			print_symbols_table_32(t_bin_file *file)
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
        if (file->symbols[i].type != 'U' && file->symbols[i].type != 'u' \
			&& file->symbols[i].type != 'I')
		{
		    ft_puthexa_uint32(file->symbols[i].value);
		}
        else
            write(1, "        ", 8);
        write(1, " ", 1);
		ft_putchar(file->symbols[i].type);
		print_name(file->symbols[i].name);
		if (file->symbols[i].type == 'I')
			ft_putstr(INDIRECT_STRING);
		write(1, "\n", 1);
        i++;
    }
}

static void			fill_one_symbol_32(t_bin_file *file, char *stringtable, \
						t_symbol *symbol, struct nlist *nlist)
{
	symbol->value = swap64_if(nlist->n_value, file->endian);
	symbol->name = (char *)is_in_file(file, \
		stringtable + swap32_if(nlist->n_un.n_strx, file->endian), \
		sizeof(*symbol->name));
	if (!symbol->name)
		symbol->name = BAD_STRING_INDEX;
	symbol->type = get_type_char(nlist->n_type, \
		nlist->n_sect, (uint64_t)nlist->n_value, file);
}

static t_ex_ret		fill_symbols_table_32(t_bin_file *file)
{
	size_t			i;
	struct nlist	*nlist;
	char			*stringtable;
	void			*check;
	uint32_t		nsyms;

	nsyms = swap32_if(file->symtab_cmd->nsyms, file->endian);
	nlist = (struct nlist *)(file->ptr \
		+ swap32_if(file->symtab_cmd->symoff, file->endian));
	check = is_in_file(file, nlist, sizeof(*nlist) * nsyms);
	stringtable = (char *)is_in_file(file, (file->ptr \
		+ file->symtab_cmd->stroff), sizeof(*stringtable));
	if (!check || !stringtable)
        return (put_error(file->filename, TRUNC_OBJECT));
	i = 0;
	while (i < nsyms)
	{
		fill_one_symbol_32(file, stringtable, &file->symbols[i], &nlist[i]);
        i++;
	}
	return (SUCCESS);
}

static t_ex_ret			get_sections_indices_32(t_bin_file *file, \
							struct segment_command *segment, uint8_t nb_sect)
{
	uint32_t 					i;
	size_t						size_sections;
	struct section				*section;
	void						*check;
	uint32_t					nsects;

	nsects = swap32_if(segment->nsects, file->endian);
	section = (struct section *)is_in_file(file, ((void *)segment \
		+ sizeof(struct segment_command)), sizeof(*section));
	size_sections = nsects * sizeof(*section);
	if (!section || !(check = is_in_file(file, section, size_sections)))
        return (put_error(file->filename, TRUNC_OBJECT));
	i = 0;
	while (i < nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = i + nb_sect;
		section = (void *)section + sizeof(struct section);
		i++;
	}
    return (SUCCESS);
}

static t_ex_ret			get_load_commands_32(t_bin_file *file, \
							struct load_command **lc, uint32_t *ncmds)
{
	struct mach_header	        *header;

	header = (struct mach_header *)is_in_file(file, file->ptr, \
		sizeof(*header));
    if (!header)
        return (put_error(file->filename, VALID_OBJECT));
	*ncmds = swap32_if(header->ncmds, file->endian);
	*lc = (struct load_command *)is_in_file(file, file->ptr + sizeof(*header), \
		sizeof(**lc));
    if (!*lc)
        return (put_error(file->filename, TRUNC_OBJECT));
	return (SUCCESS);
}

static t_ex_ret			get_info_from_load_command_32(t_bin_file *file, \
							struct load_command *lc, uint8_t *nb_sect)
{
	struct segment_command	    *segment;

	if (lc->cmd == LC_SYMTAB)
	{
		file->symtab_cmd = (struct symtab_command *)is_in_file(file, lc, \
			sizeof(*(file->symtab_cmd)));
		if (!file->symtab_cmd)
			return (put_error(file->filename, TRUNC_OBJECT));
	}
	else if (lc->cmd == LC_SEGMENT)
	{
		segment = (struct segment_command *)is_in_file(file, lc, \
			sizeof(*segment));
		if (!segment)
			return (put_error(file->filename, TRUNC_OBJECT));
		if (get_sections_indices_32(file, segment, *nb_sect) == FAILURE)
			return (FAILURE);
		*nb_sect += swap32_if(segment->nsects, file->endian);
	}
	return (SUCCESS);
}

static t_ex_ret			init_file_32(t_bin_file *file)
{
	uint32_t 						ncmds;
	struct load_command		        *lc;
	uint32_t					    i;
	uint8_t					        nb_sect;

	if (get_load_commands_32(file, &lc, &ncmds) == FAILURE)
		return (FAILURE);
	i = 0;
	nb_sect = 1;
	while (i < ncmds)
	{
		if (get_info_from_load_command_32(file, lc, &nb_sect) == FAILURE)
			return (FAILURE);
		// if ((swap32_if(lc->cmdsize, file->endian) % 8) != 0)
            // return (put_error(file->filename, TRUNC_OBJECT));
		i++;
		lc = (struct load_command *)is_in_file(file, (void *)lc \
			+ swap32_if(lc->cmdsize, file->endian), sizeof(*lc));
		if (i < ncmds && !lc)
            return (put_error(file->filename, TRUNC_OBJECT));

	}
    return (SUCCESS);
}

t_ex_ret	        handle_32(t_endian endian, char *filename, \
						size_t size, void *ptr)
{
	t_bin_file		        file;

    ft_bzero(&file, sizeof(file));
    file.filename = filename;
	file.endian = endian;
	file.ptr = ptr;
	file.size = size;
	file.end = ptr + size;
    if (init_file_32(&file) == FAILURE)
        return (FAILURE);
	if (!file.symtab_cmd)
		return (FAILURE);
    file.symbols = (t_symbol*)ft_memalloc(sizeof(t_symbol) \
		* swap32_if(file.symtab_cmd->nsyms, file.endian));
    if (!file.symbols)
		return (FAILURE);
	if (fill_symbols_table_32(&file) == FAILURE)
		return (FAILURE);
    if (sort_symbols(&file) == FAILURE)
		return (FAILURE);
	print_symbols_table_32(&file);
	free(file.symbols);
	return (SUCCESS);
}
