#include "ft_nm.h"

static t_ex_ret		run_merge_sort(t_symbol *tab, t_sort *data,
						t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	t_symbol	*tmp;
	int			i;

	data->cpt1 = data->start1;
	data->cpt2 = data->end1 + 1;
	if (!(tmp = (t_symbol *)ft_memalloc(sizeof(*tmp) \
		* (data->end1 - data->start1 + 1))))
		return (FAILURE);
	ft_memmove(tmp, tab + data->start1, (data->end1 - data->start1 + 1)
		* sizeof(*tmp));
	i = data->start1;
	while (i <= data->end2)
	{
		if (data->cpt1 == data->end1 + 1)
			break ;
		else if (data->cpt2 == data->end2 + 1)
			tab[i++] = tmp[data->cpt1++ - data->start1];
		else if (comp(tmp + data->cpt1 - data->start1, tab + data->cpt2)
			== FALSE)
			tab[i++] = tmp[data->cpt1++ - data->start1];
		else
			tab[i++] = tab[data->cpt2++];
	}
	free(tmp);
	return (SUCCESS);
}

static t_ex_ret		merge_sort(t_symbol *tab, int start_index, int end_index,
						t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	t_sort	data;
	int		middle;

	data.start1 = start_index;
	data.end1 = (end_index + start_index) / 2;
	data.end2 = end_index;
	middle = (end_index + start_index) / 2;
	if (start_index != end_index)
	{
		if (merge_sort(tab, start_index, middle, comp) == FAILURE \
				|| merge_sort(tab, middle + 1, end_index, comp) == FAILURE \
				|| run_merge_sort(tab, &data, comp) \
				== FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_ex_ret			sort_symbols(t_bin_file *file)
{
	t_bool (*comp)(t_symbol *symb1, t_symbol *symb2);

	if (is_option_activated('p'))
		return (SUCCESS);
	comp = is_option_activated('r') ? &comp_ascii_rev : &comp_ascii;
	if (is_option_activated('n'))
		comp = is_option_activated('r') ? &comp_num_rev : &comp_num;
	if (merge_sort(file->symbols, 0, \
		swap32_if(file->symtab_cmd->nsyms, file->endian) - 1, \
		comp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
