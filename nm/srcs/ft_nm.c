#include "ft_nm.h"

t_bool				g_multifile = FALSE;

static void		put_filename(char *filename, char *archive_name)
{
	if (!archive_name && g_multifile == TRUE)
	{
		ft_putendl("");
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

t_ex_ret		ft_nm(char *archive_name, char *filename, uint64_t size,
					void *ptr)
{
	t_ex_ret		ret;
	uint32_t		magic_number;

	put_filename(filename, archive_name);
	magic_number = *(uint32_t *)ptr;
	ret = FAILURE;
	if (magic_number == MH_MAGIC)
		ret = handle_32(MAGIC, filename, size, ptr);
	else if (magic_number == MH_MAGIC_64)
		ret = handle_64(MAGIC, filename, size, ptr);
	else if (magic_number == MH_CIGAM)
		ret = handle_32(CIGAM, filename, size, ptr);
	else if (magic_number == MH_CIGAM_64)
		ret = handle_64(CIGAM, filename, size, ptr);
	else if (ft_strncmp((char *)ptr, ARMAG, SARMAG) == 0)
		ret = handle_archive(filename, size, ptr);
	else if (magic_number == FAT_MAGIC)
		ret = handle_fat32(MAGIC, filename, size, ptr);
	else if (magic_number == FAT_CIGAM)
		ret = handle_fat32(CIGAM, filename, size, ptr);
	else if (magic_number == FAT_MAGIC_64)
		ft_putendl("FAT 64 MAGIC");
	else if (magic_number == FAT_CIGAM_64)
		ft_putendl("FAT 64 CIGAM");
	else
		return (put_error(filename, VALID_OBJECT));
	return (ret);
}
