#ifndef FT_NM_H
# define FT_NM_H

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>

# include "libft.h"

typedef enum	    e_ex_ret
{
	SUCCESS = EXIT_SUCCESS,
	FAILURE = EXIT_FAILURE
}                   t_ex_ret;

typedef	struct		s_symbol64 {
	// struct nlist_64			*symbole;
    char                    *name;
	char					type_char;
	uint64_t				type;
}					t_symbol64;

typedef struct		s_tools
{
	int				flag;

}					t_tools;


#endif