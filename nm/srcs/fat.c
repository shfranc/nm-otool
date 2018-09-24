/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:45:45 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/24 15:00:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

int		ft_handle_fat(void *ptr)
{
	struct fat_header	*header;
	uint32_t			nb_arch;
	struct fat_arch		*arch;

	header = (struct fat_header*)ptr;
	nb_arch = header->nfat_arch;
	printf("nb arch: %d\n", nb_arch);

	arch = ptr + sizeof(struct fat_header);
	while (nb_arch--)
	{
		printf("cputype: %d\n", arch->cputype);
		ft_nm(ptr + arch->offset);
		arch = ptr + sizeof(struct fat_arch);
	}
	return (0);
}