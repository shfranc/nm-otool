/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 16:52:12 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/25 12:58:34 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

int     ft_handle_archive(void *ptr)
{
    struct ar_hdr       *header;
    struct ar_hdr       *obj;

    header = ptr + SARMAG;
    printf("size to jump: %d\n", ft_atoi(header->ar_size));
    obj = ptr + SARMAG + sizeof(*header) + ft_atoi(header->ar_size);
    printf("obj: %s\n", obj->ar_fmag + 2);
    
    return (0);
}