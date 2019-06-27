/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:34:23 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:34:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static size_t		len_name(char *name)
{
	size_t	i;

	i = 0;
	while (i < 538)
	{
		if (!name[i])
			return (i);
		i++;
	}
	return (i);
}

void				print_name(char *name)
{
	size_t	len;

	len = len_name(name);
	if (len)
	{
		if (!is_option_activated('j') && !is_option_activated('u'))
			write(1, " ", 1);
		write(1, name, len);
	}
}
