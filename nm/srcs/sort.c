#include "ft_nm.h"

static t_bool  comp_ascii(t_symbol *symb1, t_symbol *symb2)
{
    if (ft_strcmp(symb1->name, symb2->name) > 0)
        return (TRUE);
    return (FALSE);
}

static void    bubble_sort(t_symbol *symbols, uint32_t nsyms, t_bool(*comp)(t_symbol *symb1, t_symbol *symb2))
{
    uint32_t    i;
    t_symbol    tmp;

    i = 0;
    while (i < nsyms - 1)
    {
        if (comp(&symbols[i], &symbols[i + 1]) == TRUE)
        {
            tmp = symbols[i];
            symbols[i] = symbols[i + 1];
            symbols[i + 1] = tmp;
            i = 0;
            continue ;
        }
        i++;
    }
}

void    sort_symbols(t_bin_file *file)
{
    bubble_sort(file->symbols, file->symtab_cmd->nsyms, &comp_ascii);
}