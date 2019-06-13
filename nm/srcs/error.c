#include "ft_nm.h"

t_ex_ret	put_usage(void)
{
	ft_putendl_fd("usage: ./ft_nm [-gjnpruU] binary_file [...]", 2);
	ft_putendl_fd("  -g : display only global (external) symbols", 2);
	ft_putendl_fd("  -j : display only the symbol names (no value or type)", 2);
	ft_putendl_fd("  -n : sort numerically rather than alphabetically", 2);
	ft_putendl_fd("  -p : don't sort; display in symbol-table order", 2);
	ft_putendl_fd("  -r : sort in reverse order", 2);
	ft_putendl_fd("  -u : display only undefined symbols", 2);
	ft_putendl_fd("  -U : don't display undefined symbols", 2);
	return (FAILURE);
}

t_ex_ret	illegal_option(void)
{
	ft_putendl_fd("./ft_nm: illegal option", 2);
	return (put_usage());
}

t_ex_ret	put_error(char *filename, char *message)
{
	ft_putstr_fd("ft_nm: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	return (FAILURE);
}
