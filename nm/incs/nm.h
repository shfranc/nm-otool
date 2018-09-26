/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:44:27 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/26 20:46:58 by sfranc           ###   ########.fr       */
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
# define ERR_OBJ		": The file was not recognized as a valid object file"


#include <stdio.h>

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <ar.h>

typedef struct	s_ofile {
	char			*filename;
	unsigned int	size;
	void			*data;
}				t_ofile;

extern int	g_flags;

enum 		e_error {
	NO_EXIST = -10,
	PERM_DENIED,
	NO_MMAP,
	INVALID_OBJ
};

int		ft_init_nm(char *filename);
int		ft_nm(char *filename, unsigned int size, void *data);
int		ft_process_fat(char *filename, unsigned int size, void *data);
int		ft_process_archive(char *filename, unsigned int size, void *data);
int		ft_handle_magic_64(t_ofile *file);

/*
** PARSING
*/
int		ft_get_options(int *argc, char ***argv);

/*
** TOOLS
*/
unsigned int		ft_swap_int(unsigned int n);

#endif