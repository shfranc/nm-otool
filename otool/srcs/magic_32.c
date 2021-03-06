/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:30:45 by sfranc            #+#    #+#             */
/*   Updated: 2019/06/27 15:30:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_ex_ret			get_text_section(t_bin_file *file, \
							struct segment_command *segment)
{
	uint32_t					i;
	size_t						size_sections;
	struct section				*section;
	void						*check;
	uint32_t					nsects;

	nsects = swap32_if(segment->nsects, file->endian);
	section = (struct section *)is_in_file(file, ((void *)segment \
		+ sizeof(struct segment_command)), sizeof(*section));
	size_sections = nsects * sizeof(*section);
	if (!section || !(check = is_in_file(file, section, size_sections)))
		return (put_error(file->filename, TRUNC_OBJECT));
	i = 0;
	while (i < nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			return (get_text_section_info_32(file, section));
		section = (void *)section + sizeof(struct section);
		i++;
	}
	return (SUCCESS);
}

static t_ex_ret			get_info_from_load_command_32(t_bin_file *file, \
							struct load_command *lc)
{
	struct segment_command			*segment;
	uint32_t						lc_cmd;

	lc_cmd = swap32_if(lc->cmd, file->endian);
	if (lc_cmd == LC_SEGMENT)
	{
		segment = (struct segment_command *)is_in_file(file, lc, \
			sizeof(*segment));
		if (!segment)
			return (put_error(file->filename, TRUNC_OBJECT));
		if (get_text_section(file, segment) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static t_ex_ret			get_load_commands_32(t_bin_file *file, \
							struct load_command **lc, uint32_t *ncmds)
{
	struct mach_header				*header;

	header = (struct mach_header *)is_in_file(file, file->ptr, \
		sizeof(*header));
	if (!header)
		return (put_error(file->filename, VALID_OBJECT));
	file->cputype = header->cputype;
	*ncmds = swap32_if(header->ncmds, file->endian);
	*lc = (struct load_command *)is_in_file(file, file->ptr + sizeof(*header), \
		sizeof(**lc));
	if (!*lc)
		return (put_error(file->filename, TRUNC_OBJECT));
	return (SUCCESS);
}

static t_ex_ret			init_file_32(t_bin_file *file)
{
	uint32_t						ncmds;
	struct load_command				*lc;
	uint32_t						i;

	if (get_load_commands_32(file, &lc, &ncmds) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < ncmds)
	{
		if (get_info_from_load_command_32(file, lc) == FAILURE)
			return (FAILURE);
		i++;
		lc = (struct load_command *)is_in_file(file, (void *)lc \
			+ swap32_if(lc->cmdsize, file->endian), sizeof(*lc));
		if (i < ncmds && !lc)
			return (put_error(file->filename, TRUNC_OBJECT));
	}
	return (SUCCESS);
}

t_ex_ret				handle_32(t_endian endian, char *filename, \
						size_t size, void *ptr)
{
	t_bin_file				file;

	ft_bzero(&file, sizeof(file));
	file.filename = filename;
	file.endian = endian;
	file.ptr = ptr;
	file.end = ptr + size;
	if (init_file_32(&file) == FAILURE)
		return (FAILURE);
	if (!is_in_file(&file, file.ptr + file.section_offset, \
		file.section_size))
		return (put_error(file.filename, VALID_OBJECT));
	if (display_compact(file.cputype))
		hex_dump_compact_32(&file);
	else
		hex_dump_32(&file);
	return (SUCCESS);
}
