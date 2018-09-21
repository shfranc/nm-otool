/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:44:27 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/19 11:45:02 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# define DEFAULT		"a.out"
# define OPTIONS		"agnoprumxjlfPA"
# define USAGE			"usage: ./ft_nm [ -"OPTIONS" ] [ - ] [ file ... ]"
# define ILLEGAL_OPTION	"ft_nm: illegal option\n" USAGE
# define NM_ERROR		"ft_nm: "
# define ERR_OPEN		": No such file or directory."
# define ERR_PERM		": Permission denied."
# define ERR_MMAP		": mmap error."

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>


extern int	g_flags;

enum 		e_error {
	NO_EXIST = -10,
	PERM_DENIED,
	NO_MMAP
};

int		ft_init_nm(char *filename);
int		ft_nm(char *ptr);

/*
** PARSING
*/
int		ft_get_options(int *argc, char ***argv);

#endif