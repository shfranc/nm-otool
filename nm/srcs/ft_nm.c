/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:56:57 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/24 16:55:37 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

static int		ft_open_file(char *filename, struct stat *s)
{
	int 			fd;
	
	if ((stat(filename, s)) < 0)
		return (NO_EXIST);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (PERM_DENIED);
	
	return (fd);
}

int			ft_nm(void *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	printf("magic number: %x\n", magic_number);
	
	if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
	{
		puts("FAT");
		ft_handle_fat(ptr);
	}	
	else if (magic_number == MH_MAGIC)
	{
		puts("MAGIC 32");
		// ft_handle_magic_32(ptr);
	}
	else if (magic_number == MH_MAGIC_64)
	{
		puts("MAGIC 64");
		// ft_handle_magic_64(ptr);
	}
	else if (magic_number == MH_CIGAM)
	{
		puts("CIGAM 32");
		// ft_handle_cigam_32(ptr);
	}
	else if (magic_number == MH_CIGAM_64)
	{
		puts("CIGAM 64");
		// ft_handle_cigam_64(ptr);
	}
	else if (ft_strncmp(ptr, ARCHIVE, LEN_ARCH) == 0)
	{
		puts(ARCHIVE);
		ft_handle_archive(ptr);
	}
	else
	{
		puts("something else...");
		return (INVALID_OBJ);
	}
	return (0);
}

int			ft_init_nm(char *filename)
{
	int 			fd;
	struct stat		s;
	void			*ptr;
	int				ret;


	if ((fd = ft_open_file(filename, &s)) < 0)
		return (fd);
	
	printf("filename: %s\t %d\n", filename, fd);
	printf("size: %lld\n", s.st_size);
	ptr = NULL;
	if ((ptr = mmap(ptr, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NO_MMAP);
	
	ret = ft_nm(ptr);
	
	return (ret);
}