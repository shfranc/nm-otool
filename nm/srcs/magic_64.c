/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 11:08:40 by sfranc            #+#    #+#             */
/*   Updated: 2018/10/30 10:36:07 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*elem;

	elem = ptr + symoff;
	stringtable = ptr + stroff;

	i = 0;
	while (i++ < nsyms)
	{
		if (elem[i].n_value)
			ft_puthexa_16(elem[i].n_value);
		else
			ft_putstr("                ");
		ft_putstr(" x ");
		ft_putendl(stringtable + elem[i].n_un.n_strx);		
	}
}

int		ft_handle_magic_64(void *ptr)
{
    struct mach_header_64   *header;
    unsigned int            ncmds;
	struct load_command		*lc;
    struct symtab_command	*sym;
    unsigned int			i;

    header = (struct mach_header_64*)ptr;
    ncmds = header->ncmds;
    printf("nb cmd: %d\n", ncmds);

    lc = (struct load_command*)(header + 1);
    
    i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			puts("Section SYMTAB");
			sym = (struct symtab_command *)lc;
			printf("nb symbols: %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
    return (0);
}