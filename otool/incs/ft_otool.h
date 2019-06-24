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

typedef struct				s_bin_file
{
	char					*filename;
	void					*ptr;
	void					*end;
	t_endian				endian;
	cpu_type_t				cputype;
	uint32_t				text_section_offset;
	uint64_t				text_section_addr;
	uint64_t				text_section_size;
}							t_bin_file;

t_ex_ret					ft_otool(char *archive_name, char *filename, uint64_t size,
								void *ptr);
t_ex_ret					handle_64(t_endian endian, char *filename, \
								size_t size, void *ptr);
t_ex_ret					handle_32(t_endian endian, char *filename, \
								size_t size, void *ptr);
t_ex_ret					handle_archive(char *filename, size_t size, \
								void *ptr);
t_ex_ret					handle_fat32(t_endian endian, char *filename, \
								size_t size, void *ptr);

t_bool						display_compact(cpu_type_t cpu_type);
void						hex_dump_64(t_bin_file *file);
void						hex_dump_32(t_bin_file *file);
void						hex_dump_compact_32(t_bin_file *file);
void						hex_dump_compact_64(t_bin_file *file);

void						*is_in_file(t_bin_file *file, void *dest, \
								size_t size);
uint32_t					swap32_if(uint32_t n, t_endian endian);
uint64_t					swap64_if(uint64_t n, t_endian endian);
t_bool						is_archi_x86_64(cpu_type_t cpu_type);
char						*get_archi_name(cpu_type_t cpu_type, \
								cpu_subtype_t cpu_subtype);
t_ex_ret					put_usage(void);
t_ex_ret					put_error(char *filename, char *message);
t_ex_ret					put_error_exit_success(char *filename, \
								char *message);

#endif
