#include "ft_nm.h"

static t_ex_ret			get_sections_indices_64(t_bin_file *file, \
							struct segment_command_64 *segment, uint8_t nb_sect)
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
			file->text_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = i + nb_sect;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = i + nb_sect;
		section = (void *)section + sizeof(struct section_64);
		i++;
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
	*ncmds = swap32_if(header->ncmds, file->endian);
	*lc = (struct load_command *)is_in_file(file, file->ptr + sizeof(*header), \
		sizeof(**lc));
	if (!*lc)
		return (put_error(file->filename, TRUNC_OBJECT));
	return (SUCCESS);
}

static t_ex_ret			get_info_from_load_command_64(t_bin_file *file, \
							struct load_command *lc, uint8_t *nb_sect)
{
	struct segment_command_64		*segment;
	uint32_t						lc_cmd;

	lc_cmd = swap32_if(lc->cmd, file->endian);
	if (lc_cmd == LC_SYMTAB)
	{
		file->symtab_cmd = (struct symtab_command *)is_in_file(file, lc, \
			sizeof(*(file->symtab_cmd)));
		if (!file->symtab_cmd)
			return (put_error(file->filename, TRUNC_OBJECT));
	}
	else if (lc_cmd == LC_SEGMENT_64)
	{
		segment = (struct segment_command_64 *)is_in_file(file, lc, \
			sizeof(*segment));
		if (!segment)
			return (put_error(file->filename, TRUNC_OBJECT));
		if (get_sections_indices_64(file, segment, *nb_sect) == FAILURE)
			return (FAILURE);
		*nb_sect += swap32_if(segment->nsects, file->endian);
	}
	return (SUCCESS);
}

t_ex_ret				init_file_64(t_bin_file *file)
{
	uint32_t						ncmds;
	struct load_command				*lc;
	uint32_t						i;
	uint8_t							nb_sect;

	if (get_load_commands_64(file, &lc, &ncmds) == FAILURE)
		return (FAILURE);
	i = 0;
	nb_sect = 1;
	while (i < ncmds)
	{
		if (get_info_from_load_command_64(file, lc, &nb_sect) == FAILURE)
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
