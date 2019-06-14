#include "ft_otool.h"

static void		ft_dump_hexa(const void *addr)
{
	const char	hex[16] = "0123456789abcdef";
	int			temp;

	temp = *(char*)addr >> 4 & 0x0F;
	write(1, &hex[temp], 1);
	temp = *(char*)addr & 0x0F;
	write(1, &hex[temp], 1);
}

void				print_text_section(t_bin_file *file)
{
	uint64_t i;

	ft_putendl("Contents of (__TEXT,__text) section");
	i = 0;
	while (i < file->text_section_size)
	{
		if (i % 16 == 0)
		{
			ft_puthexa_uint64(file->text_section_addr + i);
			write(1, "\t", 1);
		}
		ft_dump_hexa((const void *)(file->ptr + file->text_section_offset + i));
		write(1, " ", 1);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
	if (i % 16 != 0)
		write(1, "\n", 1);
}
