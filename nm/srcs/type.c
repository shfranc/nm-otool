/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:34:29 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:34:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char		get_section(uint8_t sect, t_bin_file *file)
{
	char	type_char;

	type_char = 'S';
	if (sect == file->text_index)
		type_char = 'T';
	else if (sect == file->data_index)
		type_char = 'D';
	else if (sect == file->bss_index)
		type_char = 'B';
	return (type_char);
}

char			get_type_char(uint8_t type, uint8_t sect, uint64_t value, \
					t_bin_file *file)
{
	uint8_t		mask;
	char		type_char;

	if (type & N_STAB)
		return ('-');
	type_char = '?';
	mask = type & N_TYPE;
	if (mask == N_UNDF && (type & N_EXT))
		type_char = 'U';
	if (mask == N_ABS)
		type_char = 'A';
	if (mask == N_INDR)
		type_char = 'I';
	if (mask == N_SECT)
		type_char = get_section(sect, file);
	if (mask == N_UNDF && value && (type & N_EXT))
		type_char = 'C';
	if (ft_isalpha(type_char) && !(type & N_EXT))
		type_char ^= TOGGLE_CASE;
	return (type_char);
}
