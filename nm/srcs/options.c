/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:34:21 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:34:22 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_bool			is_option_activated(char option)
{
	static char	*options = OPTIONS;
	char		*option_index;

	if ((option_index = ft_strchr(OPTIONS, option)) == NULL)
		return (FALSE);
	if (g_flags & (1 << (option_index - options)))
		return (TRUE);
	return (FALSE);
}

static int		save_options(char *str)
{
	static char	*options = OPTIONS;
	char		*option;

	while (*str && *str == '-')
		str++;
	while (*str)
	{
		if ((option = ft_strchr(OPTIONS, *str)) == NULL)
			return (-1);
		else
			g_flags |= (1 << (option - options));
		str++;
	}
	return (0);
}

int				get_options(int *argc, char ***argv)
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
		else if ((ret = save_options(*av)) == -1)
			return (ret);
	}
	*argv = av;
	*argc = ac;
	return (ret);
}
