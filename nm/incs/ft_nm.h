#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h> // debug

# include "libft.h"
# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>
# include <ar.h>


# define TOGGLE_CASE		32
# define BAD_STRING_INDEX	"bad string index"
# define VALID_OBJECT		"The file was not recognized as a valid object file"
// # define CMD_SIZE_ERR		"malformed object (cmdsize not a multiple of 8)"

typedef enum				e_endian
{
	MAGIC,
	CIGAM
}							t_endian;

typedef	struct				s_symbol
{
	uint64_t				value;
    char                    *name;
	char					type;
}							t_symbol;

typedef struct				s_bin_file
{
	char					*filename;
	void					*ptr;
	void					*end;
	size_t					size;
	t_endian				endian;
	uint8_t					text_index;
	uint8_t					data_index;
	uint8_t					bss_index;
	struct symtab_command	*symtab_cmd;
	t_symbol				*symbols;
}							t_bin_file;

t_ex_ret	        handle_magic_64(char *filename, t_endian endian, \
						size_t size, void *ptr);

char				get_type_char(uint8_t type, uint8_t sect, uint64_t value,
						t_bin_file *file);
t_ex_ret 			sort_symbols(t_bin_file *file);

/*
** CHECKS
*/
void        		*is_in_file(t_bin_file *file, void *current, size_t size);
uint32_t			swap32_if(uint32_t n, t_endian endian);
uint64_t			swap64_if(uint64_t n, t_endian endian);

/*
** ERRORS HANDLING
*/
t_ex_ret    		put_error(char *filename, char *message);

#endif
