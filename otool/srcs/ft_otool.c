#include "ft_otool.h"

static void		put_filename(char *filename, char *archive_name)
{
	if (!archive_name)
	{
		ft_putstr(filename);
		ft_putendl(":");
	}
	else if (archive_name)
	{
		ft_putendl("");
		ft_putstr(archive_name);
		ft_putstr("(");
		ft_putstr(filename);
		ft_putendl("):");
	}
}

t_ex_ret		ft_otool(char *archive_name, char *filename, uint64_t size,
					void *ptr)
{
	uint32_t		magic_number;

	(void)size;

	put_filename(filename, archive_name);
	magic_number = *(uint32_t *)ptr;
	return (put_error(filename, VALID_OBJECT));
}
