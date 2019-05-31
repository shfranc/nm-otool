#include "ft_nm.h"

static t_bool		is_archi_x86_64(cpu_type_t cpu_type)
{
	if (cpu_type == CPU_TYPE_X86_64)
		return (TRUE);
	return (FALSE);
}

static char    		*get_archi_name(cpu_type_t cpu_type)
{
    if (cpu_type == CPU_TYPE_I386)
        return ("i386");
    if (cpu_type == CPU_TYPE_POWERPC)
        return ("ppc");
    if (cpu_type == CPU_TYPE_POWERPC64)
        return ("ppc64");
    return ("");
}

static t_ex_ret		check_archi_x86_64(t_endian endian, uint32_t nb_arch, \
						struct fat_arch *arch, int *archi_x86_64)
{
	uint32_t	i;

	i = 0;
    while (i < nb_arch)
    {
		if (is_archi_x86_64(swap32_if(arch->cputype, endian)))
		{
			*archi_x86_64 = i;
			return (SUCCESS);
		}
		i++;
        arch++;
    }
	return (SUCCESS);
}

t_ex_ret            handle_fat32(t_endian endian, char *filename, \
						size_t size, void *ptr)
{
	struct fat_header	*header;
	uint32_t			nb_arch;
	struct fat_arch		*arch;
	int					archi_x84_64;

	(void)size;
	archi_x84_64 = -1;
	header = (struct fat_header*)ptr;
	nb_arch = swap32_if(header->nfat_arch, endian);
	arch = ptr + sizeof(struct fat_header);
	
	if (check_archi_x86_64(endian, nb_arch, arch, &archi_x84_64) == FAILURE)
		return (FAILURE);

	// display all
	if (archi_x84_64 == -1)
	{
		while (nb_arch--)
		{
			write(1, "\n", 1);
			ft_putstr(filename);
			ft_putstr(" (for architecture ");
			ft_putstr(get_archi_name(swap32_if(arch->cputype, endian)));
			ft_putendl("):");
			ft_nm(filename, swap32_if(arch->size, endian), ptr + swap32_if(arch->offset, endian));
			arch++;
		}
	}
	else
	{
		ft_nm(filename, swap32_if(arch[archi_x84_64].size, endian), \
			ptr + swap32_if(arch[archi_x84_64].offset, endian));
	}
	
    return (SUCCESS);
}
