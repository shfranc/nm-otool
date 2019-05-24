#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <stdio.h> // debug

# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>

# define TOGGLE_CASE		32
# define VALID_OBJECT		"The file was not recognized as a valid object file"

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
	unsigned int			magic_number;
	uint8_t					text_index;
	uint8_t					data_index;
	uint8_t					bss_index;
	struct symtab_command	*symtab_cmd;
	t_symbol				*symbols;
}							t_bin_file;

t_ex_ret	        handle_magic_64(char *filename, size_t size, void *ptr);

char				get_type_char(uint8_t type, uint8_t sect, uint64_t value, t_bin_file *file);
void    			sort_symbols(t_bin_file *file);

// t_bool              is_in_file(t_bin_file *file, void *dest);
void        *is_in_file(t_bin_file *file, void *current, size_t size);
t_ex_ret    		put_error(char *filename, char *message);

#endif