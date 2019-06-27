/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_archive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:36:03 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:36:04 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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
