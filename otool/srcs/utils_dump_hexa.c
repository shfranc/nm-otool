/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dump_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:31:22 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:31:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_bool		display_compact(cpu_type_t cpu_type)
{
	if (cpu_type != CPU_TYPE_X86
	&& cpu_type != CPU_TYPE_X86_64
	&& cpu_type != CPU_TYPE_I386)
		return (TRUE);
	return (FALSE);
}

void		dump_one_byte(const void *addr, char buf[3])
{
	const char	hex[16] = "0123456789abcdef";

	buf[0] = hex[(int)(*(char*)addr >> 4 & 0x0F)];
	buf[1] = hex[(int)(*(char*)addr & 0x0F)];
}

void		dump_four_bytes(const void *addr, char buf[3])
{
	const char	hex[16] = "0123456789abcdef";

	buf[6] = hex[(int)(*(char*)addr >> 4 & 0x0F)];
	buf[7] = hex[(int)(*(char*)addr & 0x0F)];
	addr++;
	buf[4] = hex[(int)(*(char*)addr >> 4 & 0x0F)];
	buf[5] = hex[(int)(*(char*)addr & 0x0F)];
	addr++;
	buf[2] = hex[(int)(*(char*)addr >> 4 & 0x0F)];
	buf[3] = hex[(int)(*(char*)addr & 0x0F)];
	addr++;
	buf[0] = hex[(int)(*(char*)addr >> 4 & 0x0F)];
	buf[1] = hex[(int)(*(char*)addr & 0x0F)];
}
