/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:39:40 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/24 16:49:30 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int 	g_flags = 0;

static void		ft_put_error(enum e_error error, char *filename)
{
	ft_putstr(NM_ERROR);
	ft_putstr(filename);
	if (error == NO_EXIST)
		ft_putendl_fd(ERR_OPEN, STDERR_FILENO);
	if (error == PERM_DENIED)
		ft_putendl_fd(ERR_PERM, STDERR_FILENO);
	if (error == NO_MMAP)
		ft_putendl_fd(ERR_MMAP, STDERR_FILENO);
	if (error == INVALID_OBJ)
		ft_putendl_fd(ERR_OBJ, STDERR_FILENO);				
}

int				main(int ac, char **av)
{
	int 	ret;
	int		final_ret;

	final_ret = EXIT_SUCCESS;
	if (ac == 1)
	{
		if ((ret = ft_init_nm(DEFAULT)) < 0)
		{
			ft_put_error(ret, DEFAULT);
			return(EXIT_FAILURE);
		}
	}
	else
	{
		if ((ft_get_options(&ac, &av)) < 0)
		{
			ft_putendl_fd(ILLEGAL_OPTION, STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		while (ac--)
		{
			if ((ret = ft_init_nm(*av)) < 0)
			{
				ft_put_error(ret, *av);
				final_ret = EXIT_FAILURE;
			}
			av++;
		}
	}
	return (final_ret);
}