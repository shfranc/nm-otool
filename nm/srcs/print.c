#include "ft_nm.h"

static size_t		len_name(char *name)
{
	size_t	i;

	i = 0;
	while (i < 538)
	{
		if (!name[i])
			return (i);
		i++;
	}
	return (i);
}

void				print_name(char *name)
{
	size_t	len;

	len = len_name(name);
	if (len)
	{
    	write(1, " ", 1);
		write(1, name, len);
	}
}
