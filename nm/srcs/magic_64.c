/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 20:15:51 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/26 21:01:15 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int     ft_handle_magic_64(t_ofile *file)
{
	unsigned int			nb_lcmds;
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;


	header = (struct mach_header_64 *)(file->data);
	nb_lcmds = header->ncmds;

	lc = (void *)(file->data) + sizeof(*header);
    printf("** NB LOAD COMMAND: %d\n", nb_lcmds);
    i = 0;
    while (i++ < nb_lcmds)
    {
        ft_putnbr_endl(lc->cmd);
        if (lc->cmd == LC_SYMTAB)
        {
			sym = (struct symtab_command *)lc;
        }
        lc = (void *)lc + lc->cmdsize;
    }
    (void)file;
    return (0);
}