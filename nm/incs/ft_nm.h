#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h> // debug

# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>

# include "libft.h"

# define TOGGLE_CASE		32

typedef enum	    		e_ex_ret
{
	SUCCESS = EXIT_SUCCESS,
	FAILURE = EXIT_FAILURE
}                   		t_ex_ret;

typedef	struct				s_symbol
{
	void					*addr;
    char                    *name;
	char					type;
}							t_symbol;

typedef struct				s_bin_file
{
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

t_ex_ret	handle_magic_64(t_bin_file *file);
char		get_type_char(uint8_t type, uint8_t sect, uint64_t value, t_bin_file *file);

#endif