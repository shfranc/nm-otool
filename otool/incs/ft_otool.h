#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "libft.h"
# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <ar.h>
# include <errno.h>

# define DEFAULT_FILE		"a.out"

# define NO_FILE			"No such file or directory."
# define PERM_DENIED		"Permission denied."
# define BAD_STRING_INDEX	"bad string index"
# define UNMAP_ERROR		"unmap: error"
# define CLOSE_ERROR		"close: error"
# define VALID_OBJECT		"The file was not recognized as a valid object file"
# define TRUNC_OBJECT		"Truncated or malformed object"

typedef enum				e_endian
{
	MAGIC,
	CIGAM
}							t_endian;

t_ex_ret					ft_otool(char *archive_name, char *filename, uint64_t size,
								void *ptr);

t_ex_ret					put_usage(void);
t_ex_ret					put_error(char *filename, char *message);

#endif
