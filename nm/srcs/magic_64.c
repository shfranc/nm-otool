#include "ft_nm.h"

static void        print_symbols_table_64(t_bin_file *file)
{
	size_t			i;

    i = 0;
	ft_putendl("=================================");
    while (i < file->symtab_cmd->nsyms)
    {
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

static void         fill_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	char			*stringtable;
	struct nlist_64	*elem;

	elem = (struct nlist_64 *)(file->ptr + file->symtab_cmd->symoff);
	stringtable = (char *)(file->ptr + file->symtab_cmd->stroff);

	i = 0;
	while (i < file->symtab_cmd->nsyms)
	{
		file->symbols[i].value = elem[i].n_value;
        file->symbols[i].name = stringtable + elem[i].n_un.n_strx;
		file->symbols[i].type = get_type_char(elem[i].n_type, elem[i].n_sect, elem[i].n_value, file);
        i++;
	}
}

static t_ex_ret	       get_sections_indices_64(t_bin_file *file, struct segment_command_64 *segment, uint8_t nb_sect)
{
	uint32_t 					i;
	struct section_64	*section;

	if (!(section = (struct section_64 *)is_in_file(file, ((void *)segment + sizeof(struct segment_command_64)), sizeof(*section))))
        return (put_error(file->filename, VALID_OBJECT));
	i = 0;
	while (i < segment->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = i + nb_sect;
		if (!(section = (struct section_64 *)is_in_file(file, ((void *)section + sizeof(struct section_64)), sizeof(*section))))
            return (put_error(file->filename, VALID_OBJECT));
		i++;
	}
    return (SUCCESS);
}

static t_ex_ret       init_file_64(t_bin_file *file, char *filename, size_t size, void *ptr)
{
	struct mach_header_64	        *header;
	struct load_command		        *lc;
	struct segment_command_64	    *segment;
	uint32_t					    i;
	uint8_t					        nb_sect;

    ft_bzero(file, sizeof(file));
    file->filename = filename;
	file->ptr = ptr;
	file->size = size;
	file->end = ptr + size;
    if (!(header = (struct mach_header_64 *)is_in_file(file, file->ptr, sizeof(*header))))
        return (put_error(file->filename, VALID_OBJECT));
    if (!(lc = (struct load_command *)is_in_file(file, file->ptr + sizeof(*header), sizeof(*lc))))
        return (put_error(file->filename, VALID_OBJECT));
	i = 0;
	nb_sect = 1;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
        {
			if (!(file->symtab_cmd = (struct symtab_command *)is_in_file(file, lc, sizeof(*(file->symtab_cmd)))))
                return (put_error(file->filename, VALID_OBJECT));
        }
		else if (lc->cmd == LC_SEGMENT_64)
		{
			if (!(segment = (struct segment_command_64 *)is_in_file(file, lc, sizeof(*segment))))
                return (put_error(file->filename, VALID_OBJECT));
			if (get_sections_indices_64(file, segment, nb_sect) == FAILURE)
                return (FAILURE);
			nb_sect += segment->nsects;
		}
        i++;
		if (!(lc = (struct load_command *)is_in_file(file, (void *)lc + lc->cmdsize, sizeof(*lc))))
            return (put_error(file->filename, VALID_OBJECT));
	}
    return (SUCCESS);
}

t_ex_ret	        handle_magic_64(char *filename, size_t size, void *ptr)
{
	t_bin_file		        file;

    if (init_file_64(&file, filename, size, ptr) == FAILURE)
        return (FAILURE);
    if (!(file.symbols = (t_symbol*)ft_memalloc(sizeof(t_symbol) * file.symtab_cmd->nsyms)))
		return (FAILURE);
	fill_symbols_table_64(&file);
    sort_symbols(&file);
	print_symbols_table_64(&file);
	free(file.symbols);
	return (SUCCESS);
}