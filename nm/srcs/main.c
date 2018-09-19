/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:39:40 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/18 18:26:42 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int 	g_flags = 0;

int		main(int ac, char **av)
{
	if (ac == 1)
		ft_nm(DEFAULT);
	else
	{
		if ((ft_get_options(&ac, &av)) == -1)
		{
			ft_putendl_fd(ILLEGAL_OPTION, STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		while (ac--)
			ft_nm(*(av++));
	}
	return (EXIT_SUCCESS);
}