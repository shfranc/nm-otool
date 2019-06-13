#include "ft_nm.h"

static void				print_one_symbol_64(t_symbol *symbol)
{
	if (symbol->type == '-' \
		|| (is_option_activated('g') && (symbol->type & TOGGLE_CASE)))
		return ;
	if (is_option_activated('u') \
		&& (symbol->type != 'U' && symbol->type != 'u'))
		return ;
	if (is_option_activated('U') \
		&& (symbol->type == 'U' || symbol->type == 'u'))
		return ;
	if (!is_option_activated('j') && !is_option_activated('u'))
	{
		if (symbol->type != 'U' && symbol->type != 'u')
			ft_puthexa_uint64(symbol->value);
		else
			write(1, "                ", 16);
		write(1, " ", 1);
		ft_putchar(symbol->type);
	}
	print_name(symbol->name);
	write(1, "\n", 1);
}

static void				print_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	uint32_t		nsyms;

	i = 0;
	nsyms = swap32_if(file->symtab_cmd->nsyms, file->endian);
	while (i < nsyms)
	{
		print_one_symbol_64(&file->symbols[i]);
		i++;
	}
}

static void				fill_one_symbol_64(t_bin_file *file, char *stringtable,\
							t_symbol *symbol, struct nlist_64 *nlist)
{
	symbol->value = swap64_if(nlist->n_value, file->endian);
	symbol->name = (char *)is_in_file(file, \
		stringtable + swap32_if(nlist->n_un.n_strx, file->endian), \
		sizeof(*symbol->name));
	if (!symbol->name)
		symbol->name = BAD_STRING_INDEX;
	symbol->type = get_type_char(nlist->n_type, \
		nlist->n_sect, symbol->value, file);
}

static t_ex_ret			fill_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	struct nlist_64	*nlist;
	char			*stringtable;
	void			*check;
	uint32_t		nsyms;

	nsyms = swap32_if(file->symtab_cmd->nsyms, file->endian);
	nlist = (struct nlist_64 *)(file->ptr \
		+ swap32_if(file->symtab_cmd->symoff, file->endian));
	check = is_in_file(file, nlist, sizeof(*nlist) * nsyms);
	stringtable = (char *)is_in_file(file, (file->ptr \
		+ swap32_if(file->symtab_cmd->stroff, file->endian)), \
		sizeof(*stringtable));
	if (!check || !stringtable)
		return (put_error(file->filename, TRUNC_OBJECT));
	i = 0;
	while (i < nsyms)
	{
		fill_one_symbol_64(file, stringtable, &file->symbols[i], &nlist[i]);
		i++;
	}
	return (SUCCESS);
}

t_ex_ret				handle_64(t_endian endian, char *filename, \
						size_t size, void *ptr)
{
	t_bin_file				file;

	ft_bzero(&file, sizeof(file));
	file.filename = filename;
	file.endian = endian;
	file.ptr = ptr;
	file.end = ptr + size;
	if (init_file_64(&file) == FAILURE)
		return (FAILURE);
	if (!file.symtab_cmd)
		return (SUCCESS);
	file.symbols = (t_symbol*)ft_memalloc(sizeof(t_symbol) \
		* swap32_if(file.symtab_cmd->nsyms, file.endian));
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
