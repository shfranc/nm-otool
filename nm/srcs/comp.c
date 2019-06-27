/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:32:25 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:32:27 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_bool		comp_ascii(t_symbol *symb1, t_symbol *symb2)
{
	if (ft_strcmp(symb1->name, symb2->name) == 0)
		return (symb1->value > symb2->value ? TRUE : FALSE);
	else if (ft_strcmp(symb1->name, symb2->name) > 0)
		return (TRUE);
	return (FALSE);
}

t_bool		comp_ascii_rev(t_symbol *symb1, t_symbol *symb2)
{
	return (comp_ascii(symb1, symb2) ? FALSE : TRUE);
}

t_bool		comp_num(t_symbol *symb1, t_symbol *symb2)
{
	return (symb1->value > symb2->value ? TRUE : FALSE);
}

t_bool		comp_num_rev(t_symbol *symb1, t_symbol *symb2)
{
	return (comp_num(symb1, symb2) ? FALSE : TRUE);
}
