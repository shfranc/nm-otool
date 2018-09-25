/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 16:52:12 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/25 18:16:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>



int     ft_handle_archive(void *ptr)
{
    struct ar_hdr       *header;
    char                *long_name;
    unsigned int        long_name_size;    
    unsigned int        symtab_size;
    struct ranlib       *obj;

    header = (struct ar_hdr)(ptr + SARMAG);
    printf("sizeof ar_hdr: %lu\n", sizeof(struct ar_hdr));
    
    write(1, "\n", 1);
    write(1, header->ar_name, 16);
    write(1, header->ar_date, 12);
    write(1, "\n", 1);
    write(1, header->ar_uid, 6);
    write(1, "\n", 1);
    write(1, header->ar_gid, 6);
    write(1, "\n", 1);
    write(1, header->ar_mode, 8);
    write(1, "\n", 1);
    write(1, header->ar_size, 10);
    write(1, "\n", 1);
    write(1, header->ar_fmag, 2);
    write(1, "\n", 1);

    long_name = (char*)(header + 1);
    printf("longname: %s\n", long_name);

    long_name_size = *(unsigned int*)(long_name + 1);
    printf("longname size: %d\n", long_name_size);
    
    symtab_size = *(int*)((void*)(header + 1) + sizeof(long_name));
    printf("size of symble table: %d\n", symtab_size);

    obj = (struct ranlib*) ((void*)(header + 1) + 24);
    // printf("ran_strx: %d\n", obj->ran_un);
    // printf("ran_name: %u\n", obj->ran_un);
    printf("ran_off: %u\n", obj->ran_off);
    
    return (0);
}