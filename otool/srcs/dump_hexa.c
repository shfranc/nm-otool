#include "ft_otool.h"

static void		dump_one_byte(const void *addr, char buf[3])
{
	const char	hex[16] = "0123456789abcdef";

	buf[0] = hex[(int)(*(char*)addr >> 4 & 0x0F)];
	buf[1] = hex[(int)(*(char*)addr & 0x0F)];
}

void				hex_dump_64(t_bin_file *file)
{
	uint64_t 	i;
	char 		buf[3];
	void		*start;

	ft_putendl("Contents of (__TEXT,__text) section");
	ft_memset(&buf, ' ', 3);
	start = file->ptr + file->text_section_offset;
	i = 0;
	while (i < file->text_section_size)
	{
		if (i % 16 == 0)
		{
			ft_puthexa_uint64(file->text_section_addr + i);
			write(1, "\t", 1);
		}
		dump_one_byte((const void *)(start + i), buf);
		write(1, buf, 3);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
	if (i % 16 != 0)
		write(1, "\n", 1);
}

void				hex_dump_32(t_bin_file *file)
{
	uint64_t 	i;
	char 		buf[3];
	void		*start;

	ft_putendl("Contents of (__TEXT,__text) section");
	ft_memset(&buf, ' ', 3);
	start = file->ptr + file->text_section_offset;
	i = 0;
	while (i < file->text_section_size)
	{
		if (i % 16 == 0)
		{
			ft_puthexa_uint32(file->text_section_addr + i);
			write(1, "\t", 1);
		}
		dump_one_byte((const void *)(start + i), buf);
		write(1, buf, 3);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
	if (i % 16 != 0)
		write(1, "\n", 1);
}
