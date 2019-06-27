/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:30:54 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:31:04 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_ex_ret	get_text_section_info_32(t_bin_file *file, struct section *section)
{
	file->section_offset = swap32_if(section->offset, file->endian);
	file->section_addr = (uint64_t)swap32_if(section->addr, file->endian);
	file->section_size = (uint64_t)swap32_if(section->size, file->endian);
	return (SUCCESS);
}

t_ex_ret	get_text_section_info_64(t_bin_file *file, \
				struct section_64 *section)
{
	file->section_offset = swap32_if(section->offset, file->endian);
	file->section_addr = swap64_if(section->addr, file->endian);
	file->section_size = swap64_if(section->size, file->endian);
	return (SUCCESS);
}
