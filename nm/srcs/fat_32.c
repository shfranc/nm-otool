#include "ft_nm.h"

static t_bool		is_archi_x86_64(cpu_type_t cpu_type)
{
	if (cpu_type == CPU_TYPE_X86_64)
		return (TRUE);
	return (FALSE);
}

static char    		*get_archi_name(cpu_type_t cpu_type, \
						cpu_subtype_t cpu_subtype)
{
    if (cpu_type == CPU_TYPE_I386)
        return ("i386");
    if (cpu_type == CPU_TYPE_POWERPC)
        return ("ppc");
    if (cpu_type == CPU_TYPE_POWERPC64)
        return ("ppc64");
    if (cpu_type == CPU_TYPE_ARM64)
        return ("arm64");
    if (cpu_type == CPU_TYPE_ARM  && cpu_subtype == CPU_SUBTYPE_ARM_V7)
        return ("armv7");
    if (cpu_type == CPU_TYPE_ARM  && cpu_subtype == CPU_SUBTYPE_ARM_V7S)
        return ("armv7s");
    return ("");
}

static t_ex_ret		check_archi_x86_64(t_bin_file *file, uint32_t nb_arch, \
						struct fat_arch *arch, int *archi_x86_64)
{
	uint32_t		i;
	void			*check;

	check = is_in_file(file, arch, sizeof(struct fat_arch) * nb_arch);
	if (!check)
		return (put_error(file->filename, TRUNC_OBJECT));
	i = 0;
    while (i < nb_arch)
    {
		check = is_in_file(file, file->ptr + swap32_if(arch->offset, file->endian), swap32_if(arch->size, file->endian));
		if (!check)
				return (put_error(file->filename, TRUNC_OBJECT));
		if (is_archi_x86_64(swap32_if(arch->cputype, file->endian)))
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
	t_bin_file			file;
	struct fat_header	*header;
	uint32_t			nb_arch;
	struct fat_arch		*arch;
	int					archi_x84_64;

    ft_bzero(&file, sizeof(file));
    file.filename = filename;
	file.endian = endian;
	file.ptr = ptr;
	file.end = ptr + size;

	archi_x84_64 = -1;

	header = (struct fat_header*)is_in_file(&file, ptr, sizeof(*header));
	if (!header)
        return (put_error(file.filename, VALID_OBJECT));
	
	nb_arch = swap32_if(header->nfat_arch, file.endian);
	ft_putnbr_endl(nb_arch);
	arch = ptr + sizeof(struct fat_header);
	if (check_archi_x86_64(&file, nb_arch, arch, &archi_x84_64) == FAILURE)
		return (FAILURE);

	if (archi_x84_64 == -1)
	{
		while (nb_arch--)
		{
			write(1, "\n", 1);
			ft_putstr(filename);
			ft_putstr(" (for architecture ");
			ft_putstr(get_archi_name(swap32_if(arch->cputype, file.endian), \
				swap32_if(arch->cpusubtype, file.endian)));
			ft_putendl("):");
			if (ft_nm(filename, swap32_if(arch->size, file.endian), file.ptr + swap32_if(arch->offset, file.endian)) == FAILURE)
			{
				return (FAILURE);
			}
			arch++;
		}
	}
	else
	{
		if (ft_nm(filename, swap32_if(arch[archi_x84_64].size, file.endian), \
			file.ptr + swap32_if(arch[archi_x84_64].offset, file.endian)) == FAILURE)
		{
			return (FAILURE);
		}
	}
	
    return (SUCCESS);
}
