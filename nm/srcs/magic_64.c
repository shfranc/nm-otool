#include "ft_nm.h"

static void        fill_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	char			*stringtable;
	struct nlist_64	*elem;

	elem = file->ptr + file->symtab_cmd->symoff;
	stringtable = file->ptr + file->symtab_cmd->stroff;

	i = 0;
	while (i < file->symtab_cmd->nsyms)
	{
		file->symbols[i].value = elem[i].n_value;
        file->symbols[i].name = stringtable + elem[i].n_un.n_strx;
		file->symbols[i].type = get_type_char(elem[i].n_type, elem[i].n_sect, elem[i].n_value, file);
        i++;
	}
}

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

static void	       get_sections_indices_64(t_bin_file *file, struct segment_command_64 *segment, uint8_t nb_sect)
{
	uint32_t 					i;
	struct section_64	*section;

	section = (struct section_64 *)((void *)segment + sizeof(struct segment_command_64));
	i = 0;
	while (i < segment->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = i + nb_sect;
		section = (struct section_64 *)((void *)section + sizeof(struct section_64));
		i++;
	}
}

t_ex_ret	        handle_magic_64(t_bin_file *file)
{
	int						cmd_number;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct segment_command_64	*segment;
	uint8_t					nb_sect;

	// init file
    (void)file->size;
	header = (struct mach_header_64 *)file->ptr;
	cmd_number = header->ncmds;

	lc = file->ptr + sizeof(*header);
	i = 0;
	nb_sect = 1;
	while (i < cmd_number)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			puts("Section SYMTAB");
			file->symtab_cmd = (struct symtab_command *)lc;
			printf("nb symbols: %d\n", file->symtab_cmd->nsyms);
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)lc;
			get_sections_indices_64(file, segment, nb_sect);
			nb_sect += segment->nsects;
		}
        i++;
		
		lc = (void *)lc + lc->cmdsize;
	}

	// nm process
    if (!(file->symbols = (t_symbol*)ft_memalloc(sizeof(t_symbol) * file->symtab_cmd->nsyms)))
		return (FAILURE);
	fill_symbols_table_64(file);
	print_symbols_table_64(file);
    sort_symbols(file);
	print_symbols_table_64(file);
	free(file->symbols);
	return (SUCCESS);

    return (FAILURE);
}