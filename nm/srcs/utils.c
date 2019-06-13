#include "ft_nm.h"

void		*is_in_file(t_bin_file *file, void *dest, size_t size)
{
	void		*max;

	max = dest + size;
	if (dest >= file->ptr && dest < file->end \
		&& max > file->ptr && max <= file->end)
		return (dest);
	return (NULL);
}

uint32_t	swap32_if(uint32_t n, t_endian endian)
{
	if (endian == MAGIC)
		return (n);
	else
		return (ft_swap_uint32(n));
}

uint64_t	swap64_if(uint64_t n, t_endian endian)
{
	if (endian == MAGIC)
		return (n);
	else
		return (ft_swap_uint64(n));
}

t_bool		is_archi_x86_64(cpu_type_t cpu_type)
{
	if (cpu_type == CPU_TYPE_X86_64)
		return (TRUE);
	return (FALSE);
}

char		*get_archi_name(cpu_type_t cpu_type, \
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
	if (cpu_type == CPU_TYPE_ARM && cpu_subtype == CPU_SUBTYPE_ARM_V7)
		return ("armv7");
	if (cpu_type == CPU_TYPE_ARM && cpu_subtype == CPU_SUBTYPE_ARM_V7S)
		return ("armv7s");
	return ("");
}
