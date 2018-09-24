/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:45:45 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/24 16:06:17 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

int		ft_handle_fat(void *ptr)
{
	struct fat_header	*header;
	unsigned int		nb_arch;
	struct fat_arch		*arch;

	header = (struct fat_header*)ptr;
	nb_arch = ft_swap_int(header->nfat_arch);
	printf("nb arch: %d\n", nb_arch);

	arch = ptr + sizeof(struct fat_header);
	while (nb_arch--)
	{
		printf("cputype: %d\n", ft_swap_int(arch->cputype));
		printf("cputype: %d\n", ft_swap_int(arch->cpusubtype));
		ft_nm(ptr + ft_swap_int(arch->offset));
		arch = (void*)arch + sizeof(struct fat_arch);
	}
	return (0);
}