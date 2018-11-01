/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:56:57 by sfranc            #+#    #+#             */
/*   Updated: 2018/11/01 14:44:54 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		ft_open_file(char *filename, struct stat *s)
{
	int 			fd;
	
	if ((stat(filename, s)) < 0)
		return (NO_EXIST);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (PERM_DENIED);
	
	return (fd);
}

static void		ft_init_ofile(t_ofile *file, char *filename, unsigned int size, void *data)
{
	file->filename = filename;
	file->size = size;
	file->data = data;
	printf("file: %s\tsize: %d\n", file->filename, file->size);
}

int			ft_nm(char *filename, unsigned int size, void *data)
{
	unsigned int	magic_number;
	t_ofile			file;

	ft_init_ofile(&file, filename, size, data);

	magic_number = *(int *)data;
	printf("magic number: %x\n", magic_number);
	
	if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
	{
		puts("FAT");
		ft_process_fat(filename, size, data);
	}	
	else if (magic_number == MH_MAGIC)
	{
		puts("MAGIC 32");
		// ft_handle_magic_32(data);
	}
	else if (magic_number == MH_MAGIC_64)
	{
		puts("MAGIC 64");
<<<<<<< HEAD
		ft_handle_magic_64(ptr);
=======
		ft_handle_magic_64(&file);
>>>>>>> 6988f7e80844b596b149661d40dfcc68adb6ef90
	}
	else if (magic_number == MH_CIGAM)
	{
		puts("CIGAM 32");
		// ft_handle_cigam_32(data);
	}
	else if (magic_number == MH_CIGAM_64)
	{
		puts("CIGAM 64");
		// ft_handle_cigam_64(data);
	}
	else if (ft_strncmp(data, ARMAG, SARMAG) == 0)
	{
		puts(ARMAG);
		ft_process_archive(filename, size, data);
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
	void			*data;
	int				ret;


	if ((fd = ft_open_file(filename, &s)) < 0)
		return (fd);
	
	data = NULL;
	if ((data = mmap(data, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NO_MMAP);
	
	ret = ft_nm(filename, s.st_size, data);
	
	return (ret);
}