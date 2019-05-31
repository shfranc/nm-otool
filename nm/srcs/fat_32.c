#include "ft_nm.h"

t_ex_ret            handle_fat32(t_endian endian, char *filename, \
						size_t size, void *ptr)
{
	struct fat_header	*header;
	uint32_t			nb_arch;
	struct fat_arch		*arch;

	(void)endian;
	(void)filename;
	(void)size;

	header = (struct fat_header*)ptr;
	nb_arch = swap32_if(header->nfat_arch, endian);
	printf("nb arch: %d\n", nb_arch);

	arch = ptr + sizeof(struct fat_header);
    while (nb_arch--)
    {
        printf("cputype: %d\n", swap32_if(arch->cputype, endian));
        printf("cpusubtype: %d\n", swap32_if(arch->cpusubtype, endian));
        ft_nm(filename, swap32_if(arch->size, endian), ptr + swap32_if(arch->offset, endian));
        arch++;
    }
    return (SUCCESS);
}
