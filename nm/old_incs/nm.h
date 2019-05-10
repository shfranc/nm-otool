#ifndef NM_H
# define NM_H

# include <stdio.h>

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <ar.h>

/*
** USAGE
*/

# define DEFAULT		"a.out"
# define OPTIONS		"agnoprumxjlfPA"
# define USAGE			"usage: ./ft_nm [ -"OPTIONS" ] [ - ] [ file ... ]"
# define ILLEGAL_OPTION	"ft_nm: illegal option\n" USAGE

/*
** ERRORS
*/

# define NM_ERROR		"ft_nm: "
# define ERR_OPEN		": No such file or directory."
# define ERR_PERM		": Permission denied."
# define ERR_MMAP		": mmap error."
# define ERR_OBJ		": The file was not recognized as a valid object file"
# define ERR_MALLOC		": Unable to malloc."

/*
** GLOBAL VARIABLES
*/

extern int	g_flags;

/*
** STRUCTURES
*/

enum 				e_error {
	NO_EXIST = -10,
	PERM_DENIED,
	NO_MMAP,
	INVALID_OBJ,
	MALLOC_FAILED
};

typedef	struct		s_symbole64 {
	struct nlist_64			*symbole;
	struct s_symbole		*next;
	struct s_symbole		*prev;
}					t_symbole64;

typedef struct		s_file64 {
	void					*ptr;
	struct mach_header_64   *header;
	struct load_command		*load_cmds;
    struct symtab_command	*symtab_cmd;
	t_symbole64				*symboles;
}					t_file64;

/*
** NM
*/

int					ft_init_nm(char *filename);
int					ft_nm(char *filename, unsigned int size, void *ptr);
int					ft_process_fat(char *filename, unsigned int size, void *ptr);
int					ft_process_archive(char *filename, unsigned int size, void *ptr);
int					ft_handle_magic_64(void *ptr);


/*
** TOOLS
*/
int					get_options(int *argc, char ***argv);
void				ft_puthexa_16(unsigned long long nbr);

#endif