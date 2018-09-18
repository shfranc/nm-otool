/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:13:07 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/18 18:39:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		ft_save_options(char *str)
{
	static char	*options = OPTIONS;
	char		*option;
	
	while(*str && *str == '-')
		str++;
	while (*str)
	{
		if ((option = ft_strchr(OPTIONS, *str)) == NULL)
			return (-1);
		else
			g_flags |= ( 1 << (option - options));
		str++;
	}
	printbit(g_flags);
	return (0);
}

int				ft_get_options(int *argc, char ***argv)
{
	int		ret;
	int		ac;
	char	**av;

	ret = 0;

	av = *argv;
	ac = *argc;
	while (--ac)
	{
		++av;
		if (ft_strequ(*av, "-") || ft_strequ(*av, "--"))
		{
			++av;
			break ;
		}
		if (**av != '-')
			break ;
		else if ((ret = ft_save_options(*av)) == -1)
			return (ret);
	}
	
	*argv = av;
	*argc = ac;
	return (ret);
}