/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:56:57 by sfranc            #+#    #+#             */
/*   Updated: 2018/09/19 11:51:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

static int		ft_open_file(char *filename)
{
	int 			fd;
	struct stat		s;
	
	if ((stat(filename, &s)) < 0)
		return (NO_EXIST);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (PERM_DENIED);
	printf("size: %lld\n", s.st_size);
	
	return (0);
}

int			ft_nm(char *filename)
{
	int ret;

	if ((ret = ft_open_file(filename)) < 0)
		return (ret);
	printf("filename: %s\n", filename);
	
	return (0);
}