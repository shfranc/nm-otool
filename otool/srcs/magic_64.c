#include "ft_otool.h"

static t_ex_ret			get_text_section(t_bin_file *file, \
							struct segment_command_64 *segment)
{
	uint32_t					i;
	size_t						size_sections;
	struct section_64			*section;
	void						*check;
	uint32_t					nsects;

	nsects = swap32_if(segment->nsects, file->endian);
	section = (struct section_64 *)is_in_file(file, ((void *)segment \
		+ sizeof(struct segment_command_64)), sizeof(*section));
	size_sections = nsects * sizeof(*section);
	if (!section || !(check = is_in_file(file, section, size_sections)))
		return (put_error(file->filename, TRUNC_OBJECT));
	i = 0;
	while (i < nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
		{
			file->text_section_offset = swap32_if(section->offset, file->endian);
			file->text_section_addr = swap64_if(section->addr, file->endian);
			file->text_section_size = swap64_if(section->size, file->endian);
			return (SUCCESS);
		}
		section = (void *)section + sizeof(struct section_64);
		i++;
	}
	return (SUCCESS);
}

static t_ex_ret			get_info_from_load_command_64(t_bin_file *file, \
							struct load_command *lc)
{
	struct segment_command_64		*segment;
	uint32_t						lc_cmd;

	lc_cmd = swap32_if(lc->cmd, file->endian);
	if (lc_cmd == LC_SEGMENT_64)
	{
		segment = (struct segment_command_64 *)is_in_file(file, lc, \
			sizeof(*segment));
		if (!segment)
			return (put_error(file->filename, TRUNC_OBJECT));
		// if (ft_strcmp(segment->segname, SEG_TEXT) == 0)
		// {
			if (get_text_section(file, segment) == FAILURE)
				return (FAILURE);
		// }
	}
	return (SUCCESS);
}

static t_ex_ret			get_load_commands_64(t_bin_file *file, \
							struct load_command **lc, uint32_t *ncmds)
{
	struct mach_header_64			*header;

	header = (struct mach_header_64 *)is_in_file(file, file->ptr, \
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

static t_ex_ret			init_file_64(t_bin_file *file)
{
	uint32_t						ncmds;
	struct load_command				*lc;
	uint32_t						i;

	if (get_load_commands_64(file, &lc, &ncmds) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < ncmds)
	{
		if (get_info_from_load_command_64(file, lc) == FAILURE)
			return (FAILURE);
		if ((swap32_if(lc->cmdsize, file->endian) % 8) != 0)
			return (put_error(file->filename, TRUNC_OBJECT));
		i++;
		lc = (struct load_command *)is_in_file(file, (void *)lc \
			+ swap32_if(lc->cmdsize, file->endian), sizeof(*lc));
		if (i < ncmds && !lc)
			return (put_error(file->filename, TRUNC_OBJECT));
	}
	return (SUCCESS);
}

t_ex_ret				handle_64(t_endian endian, char *filename, \
						size_t size, void *ptr)
{
	t_bin_file				file;

	ft_bzero(&file, sizeof(file));
	file.filename = filename;
	file.endian = endian;
	file.ptr = ptr;
	file.end = ptr + size;
	if (init_file_64(&file) == FAILURE)
		return (FAILURE);
	if (display_compact(file.cputype))
		hex_dump_compact_64(&file);
	else
		hex_dump_64(&file);
	return (SUCCESS);
}
