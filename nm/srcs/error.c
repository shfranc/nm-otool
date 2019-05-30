#include "ft_nm.h"

t_ex_ret    put_error(char *filename, char *message)
{
    ft_putstr_fd("ft_nm: ", STDERR_FILENO);
    ft_putstr_fd(filename, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putendl_fd(message, STDERR_FILENO);
    return (FAILURE);
}