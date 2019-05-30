#include "ft_nm.h"

static t_bool   comp_ascii(t_symbol *symb1, t_symbol *symb2)
{
    if (ft_strcmp(symb1->name, symb2->name) == 0)
        return (symb1->value >= symb2->value ? TRUE : FALSE);
    else if (ft_strcmp(symb1->name, symb2->name) > 0)
		return (TRUE);
    return (FALSE);
}

static t_ex_ret run_merge_sort(t_symbol *tab, int start1, int end1, int end2,
                    t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
    t_symbol    *tmp;
    int        cpt1;
    int        cpt2;
    int        i;

    cpt1 = start1;
    cpt2 = end1 + 1;
    if (!(tmp = (t_symbol *)ft_memalloc(sizeof(*tmp) * (end1 - start1 + 1))))
        return (FAILURE);
    ft_memmove(tmp, tab + start1, (end1 - start1 + 1) * sizeof(*tmp));
    i = start1;
    while (i <= end2)
    {
        if (cpt1 == end1 + 1)
            break ;
        else if (cpt2 == end2 + 1)
            tab[i] = tmp[cpt1++ - start1];
        else if (comp(tmp + cpt1 - start1, tab + cpt2) == FALSE)
            tab[i] = tmp[cpt1++ - start1];
        else
            tab[i] = tab[cpt2++];
        i++;
    }
    free(tmp);
    return (SUCCESS);
}

static t_ex_ret merge_sort(t_symbol *tab, int start_index, int end_index,
                    t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
    int        middle;

    middle = (end_index + start_index) / 2;
    if (start_index != end_index)
    {
        if (merge_sort(tab, start_index, middle, comp) == FAILURE
            || merge_sort(tab, middle + 1, end_index, comp) == FAILURE
            || run_merge_sort(tab, start_index, middle, end_index, comp)
                == FAILURE)
            return (FAILURE);
    }
    return (SUCCESS);
}

t_ex_ret           sort_symbols(t_bin_file *file)
{
    if (merge_sort(file->symbols, 0, file->symtab_cmd->nsyms - 1, &comp_ascii) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}
