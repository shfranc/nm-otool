/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:30:32 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:30:34 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_ex_ret	put_usage(void)
{
	ft_putendl_fd("usage: ./ft_otoot binary_file [...]", 2);
	return (FAILURE);
}

t_ex_ret	put_error(char *filename, char *message)
{
	ft_putstr_fd("ft_otool: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	return (FAILURE);
}

t_ex_ret	put_error_exit_success(char *filename, char *message)
{
	ft_putstr_fd("ft_otool: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	return (SUCCESS);
}
