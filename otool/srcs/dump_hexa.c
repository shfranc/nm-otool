/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:30:29 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:30:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				hex_dump_compact_64(t_bin_file *file)
{
	uint64_t	i;
	uint64_t	j;
	char		buf[9];
	void		*start;

	ft_putendl("Contents of (__TEXT,__text) section");
	ft_memset(&buf, ' ', 9);
	start = file->ptr + file->section_offset;
	i = 0;
	j = 0;
	while (i < file->section_size)
	{
		if (j % 4 == 0)
		{
			ft_puthexa_uint64(file->section_addr + i);
			write(1, "\t", 1);
		}
		dump_four_bytes((const void *)(start + i), buf);
		write(1, buf, 9);
		if (j++ % 4 == 3)
			write(1, "\n", 1);
		i += 4;
	}
	if (i % 16 != 0)
		write(1, "\n", 1);
}

void				hex_dump_64(t_bin_file *file)
{
	uint64_t	i;
	char		buf[3];
	void		*start;

	ft_putendl("Contents of (__TEXT,__text) section");
	ft_memset(&buf, ' ', 3);
	start = file->ptr + file->section_offset;
	i = 0;
	while (i < file->section_size)
	{
		if (i % 16 == 0)
		{
			ft_puthexa_uint64(file->section_addr + i);
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

void				hex_dump_compact_32(t_bin_file *file)
{
	uint64_t	i;
	uint64_t	j;
	char		buf[9];
	void		*start;

	ft_putendl("Contents of (__TEXT,__text) section");
	ft_memset(&buf, ' ', 9);
	start = file->ptr + file->section_offset;
	i = 0;
	j = 0;
	while (i < file->section_size)
	{
		if (j % 4 == 0)
		{
			ft_puthexa_uint32(file->section_addr + i);
			write(1, "\t", 1);
		}
		dump_four_bytes((const void *)(start + i), buf);
		write(1, buf, 9);
		if (j++ % 4 == 3)
			write(1, "\n", 1);
		i += 4;
	}
	if (i % 16 != 0)
		write(1, "\n", 1);
}

void				hex_dump_32(t_bin_file *file)
{
	uint64_t	i;
	char		buf[3];
	void		*start;

	ft_putendl("Contents of (__TEXT,__text) section");
	ft_memset(&buf, ' ', 3);
	start = file->ptr + file->section_offset;
	i = 0;
	while (i < file->section_size)
	{
		if (i % 16 == 0)
		{
			ft_puthexa_uint32(file->section_addr + i);
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
