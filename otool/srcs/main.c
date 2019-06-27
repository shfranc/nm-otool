/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:30:51 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:30:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_ex_ret		process_one_file(char *filename)
{
	t_ex_ret	ret;
	int			fd;
	struct stat buf;
	void		*ptr;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || fstat(fd, &buf) < 0)
	{
		if (errno == EACCES)
			return (put_error(filename, PERM_DENIED));
		else
			return (put_error(filename, NO_FILE));
	}
	ptr = NULL;
	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) \
		== MAP_FAILED)
		return (put_error(filename, VALID_OBJECT));
	ret = ft_otool(NULL, filename, (uint64_t)buf.st_size, ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (put_error(filename, UNMAP_ERROR));
	if (close(fd) < 0)
		return (put_error(filename, CLOSE_ERROR));
	return (ret);
}

int					main(int ac, char **av)
{
	t_ex_ret ret;

	ret = SUCCESS;
	if (ac < 2)
		return (put_usage());
	av++;
	while (--ac)
	{
		if (process_one_file(*av++) == FAILURE)
			ret = FAILURE;
	}
	return (ret);
}
