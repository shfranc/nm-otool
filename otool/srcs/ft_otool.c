#include "ft_otool.h"

static void		put_filename(char *filename, char *archive_name, char *ptr)
{
	if (!archive_name && ft_strncmp((char *)ptr, ARMAG, SARMAG) == 0)
	{
		ft_putstr("Archive : ");
		ft_putendl(filename);
	}
	else if (!archive_name)
	{
		ft_putstr(filename);
		ft_putendl(":");
	}
	else if (archive_name)
	{
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

	put_filename(filename, archive_name, ptr);
	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC)
		return (handle_32(MAGIC, filename, size, ptr));
	if (magic_number == MH_MAGIC_64)
		return (handle_64(MAGIC, filename, size, ptr));
	if (magic_number == MH_CIGAM)
		return (handle_32(CIGAM, filename, size, ptr));
	if (magic_number == MH_CIGAM_64)
		return (handle_64(CIGAM, filename, size, ptr));
	if (ft_strncmp((char *)ptr, ARMAG, SARMAG) == 0)
		return (handle_archive(filename, size, ptr));
	if (magic_number == FAT_MAGIC)
		return (handle_fat32(MAGIC, filename, size, ptr));
	if (magic_number == FAT_CIGAM)
		return (handle_fat32(CIGAM, filename, size, ptr));
	// if (magic_number == FAT_MAGIC_64)
		// return (handle_fat64(MAGIC, filename, size, ptr));
	// if (magic_number == FAT_CIGAM_64)
		// return (handle_fat64(CIGAM, filename, size, ptr));
	return (put_error_exit_success(filename, VALID_OBJECT));
}
