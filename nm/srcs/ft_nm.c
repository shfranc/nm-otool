#include "ft_nm.h"

t_ex_ret	ft_nm(char *filename, uint64_t size, void *ptr)
{
    t_ex_ret        ret;
	uint32_t		magic_number;

	magic_number = *(uint32_t *)ptr;
    ret = FAILURE;
	// printf("magic number: %x\n", magic_number);

    if (magic_number == MH_MAGIC)
    {
		// ft_putendl("MAGIC 32 bits");
		ret = handle_32(MAGIC, filename, size, ptr);
	}
    else if (magic_number == MH_MAGIC_64)
	{
		// ft_putendl("MAGIC 64 bits");
		ret = handle_64(MAGIC, filename, size, ptr);
	}
    else if (magic_number == MH_CIGAM)
    {
		// ft_putendl("CIGAM 32 bits");
		ret = handle_32(CIGAM, filename, size, ptr);
	}
    else if (magic_number == MH_CIGAM_64)
    {
		// ft_putendl("CIGAM 64 bits");
		ret = handle_64(CIGAM, filename, size, ptr);
	}
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
	{
		// ft_putendl(ARMAG);
	}
	else if (magic_number == FAT_MAGIC)
	{
		// ft_putendl("FAT 32 MAGIC");
		ret = handle_fat32(MAGIC, filename, size, ptr);
	}
	else if (magic_number == FAT_CIGAM)
	{
		// ft_putendl("FAT 32 CIGAM");
		ret = handle_fat32(CIGAM, filename, size, ptr);
	}
	else if (magic_number == FAT_MAGIC_64)
	{
		// ft_putendl("FAT 64 MAGIC");
	}
	else if (magic_number == FAT_CIGAM_64)
	{
		// ft_putendl("FAT 64 CIGAM");
	}
	else
		ft_putendl("something else...");

    return (ret);
}
