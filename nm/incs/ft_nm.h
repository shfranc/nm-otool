#ifndef FT_NM_H
# define FT_NM_H

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

# define OPTIONS			"gjnpruU"
# define TOGGLE_CASE		32
# define NO_FILE			"No such file or directory."
# define PERM_DENIED		"Permission denied."
# define BAD_STRING_INDEX	"bad string index"
# define INDIRECT_STRING	" (indirect for ?)"
# define UNMAP_ERROR		"unmap: error"
# define VALID_OBJECT		"The file was not recognized as a valid object file"
# define TRUNC_OBJECT		"Truncated or malformed object"

extern int					g_flags;
extern t_bool				g_multifile;

typedef enum				e_endian
{
	MAGIC,
	CIGAM
}							t_endian;

typedef	struct				s_symbol
{
	uint64_t				value;
	char					*name;
	char					type;
}							t_symbol;

typedef struct				s_bin_file
{
	char					*filename;
	void					*ptr;
	void					*end;
	t_endian				endian;
	uint8_t					text_index;
	uint8_t					data_index;
	uint8_t					bss_index;
	struct symtab_command	*symtab_cmd;
	t_symbol				*symbols;
}							t_bin_file;

typedef struct				s_sort
{
	int						start1;
	int						end1;
	int						end2;
	int						cpt1;
	int						cpt2;
}							t_sort;


t_ex_ret					ft_nm(char *archive_name, char *filename, \
								uint64_t size, void *ptr);
t_ex_ret					handle_32(t_endian endian, char *filename, \
								size_t size, void *ptr);
t_ex_ret					handle_64(t_endian endian, char *filename, \
								size_t size, void *ptr);
t_ex_ret					handle_fat32(t_endian endian, char *filename, \
								size_t size, void *ptr);
t_ex_ret					handle_archive(char *filename, size_t size, \
								void *ptr);

int							get_options(int *argc, char ***argv);
char						get_type_char(uint8_t type, uint8_t sect, \
								uint64_t value, t_bin_file *file);
t_ex_ret					sort_symbols(t_bin_file *file);
void						print_name(char *name);

/*
** CHECKS
*/
void						*is_in_file(t_bin_file *file, void *current, \
								size_t size);
uint32_t					swap32_if(uint32_t n, t_endian endian);
uint64_t					swap64_if(uint64_t n, t_endian endian);

/*
** ERRORS HANDLING
*/
t_ex_ret					put_usage(void);
t_ex_ret					illegal_option(void);
t_ex_ret					put_error(char *filename, char *message);

#endif
