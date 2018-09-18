/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:44:27 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/18 18:24:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# define DEFAULT		"a.out"
# define OPTIONS		"agnoprumxjlfPA"
# define USAGE			"usage: ./ft_nm [ -agnoprumxjlfPA ] [ - ] [ file ... ]"
# define ILLEGAL_OPTION	"ft_nm: illegal option\n" USAGE

# include "libft.h"

extern int	g_flags;

void	ft_nm(char *filename);

/*
** PARSING
*/
int		ft_get_options(int *argc, char ***argv);

#endif