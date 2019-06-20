#include "ft_otool.h"

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

t_bool		display_compact(cpu_type_t cpu_type)
{
	if (cpu_type != CPU_TYPE_X86
	&& cpu_type != CPU_TYPE_X86_64
	&& cpu_type != CPU_TYPE_I386)
		return (TRUE);
	return (FALSE);
}
