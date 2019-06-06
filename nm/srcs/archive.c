#include "ft_nm.h"

static uint32_t     ft_padding_ar_mac(char *ar_name)
{
    if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
        return ((uint32_t)ft_atoi(ar_name + ft_strlen(AR_EFMT1)));
    else
        return (0);
}

static t_ex_ret	loop_through_archive(t_bin_file *file,
					struct ar_hdr *object_header)
{
	char				*object_name;
	void				*object_ptr;
	uint32_t			object_size;

	while (object_header)
	{
		object_name = (char*)(object_header + 1);
		object_ptr = object_name + ft_padding_ar_mac(object_header->ar_name);
		object_size = ft_atoi(object_header->ar_size);
		if (!is_in_file(file, object_ptr, object_size \
			- ft_padding_ar_mac(object_header->ar_name)))
		{
			return (put_error(object_name, TRUNC_OBJECT));
		}
		if (ft_nm(file->filename, object_name, object_size, object_ptr))
			return (FAILURE);
		object_header = (struct ar_hdr*)is_in_file(file, object_name \
			+ object_size, sizeof(*object_header));
	}
	return (SUCCESS);
}

static t_ex_ret	check_valid_archive(t_bin_file *file, struct ar_hdr *header,
				uint32_t *symtab_size, uint32_t *string_table_size)
{
    struct ranlib       *symtab;

    *symtab_size = *(uint32_t*)is_in_file(file, ((void*)(header + 1) \
		+ ft_padding_ar_mac(header->ar_name)), sizeof(uint32_t));
	if (!symtab_size)
		return (put_error(file->filename, TRUNC_OBJECT));
    symtab = (struct ranlib*)is_in_file(file, ((void*)(header + 1) \
		+ ft_padding_ar_mac(header->ar_name) + sizeof(uint32_t)), *symtab_size);
	if (!symtab)
		return (put_error(file->filename, TRUNC_OBJECT));
	*string_table_size = *(uint32_t*)is_in_file(file, ((void*)symtab \
		+ *symtab_size), sizeof(uint32_t));
	if (!string_table_size)
		return (put_error(file->filename, TRUNC_OBJECT));
	return (SUCCESS);
}

static void		init_file(t_bin_file *file, char *filename, size_t size,
					void *ptr)
{
	file->ptr = ptr;
	file->end = ptr + size;
	file->filename = filename;
}

t_ex_ret     handle_archive(char *filename, size_t size, void *ptr)
{
	t_bin_file			file;
    struct ar_hdr       *header;
    uint32_t        	symtab_size;
	uint32_t			string_table_size;
    struct ar_hdr       *object_header;

	init_file(&file, filename, size, ptr);
	symtab_size = 0;
	string_table_size = 0;
    header = (struct ar_hdr*)is_in_file(&file, ptr + SARMAG, sizeof(*header));
	if (!header)
		return (put_error(filename, VALID_OBJECT));
	if (check_valid_archive(&file, header, &symtab_size, &string_table_size) \
		== FAILURE)
	{
		return (FAILURE);
	}
    object_header = (struct ar_hdr*)is_in_file(&file, (void*)(header + 1) \
		+ ft_padding_ar_mac(header->ar_name) + sizeof(uint32_t) \
		+ symtab_size + sizeof(uint32_t) \
		+ string_table_size, sizeof(*object_header));
	if (!object_header)
		return (put_error(filename, TRUNC_OBJECT));
    return (loop_through_archive(&file, object_header));
}
