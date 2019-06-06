#include "ft_nm.h"

static uint32_t     ft_padding_ar_mac(char *ar_name)
{
    if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
        return ((uint32_t)ft_atoi(ar_name + ft_strlen(AR_EFMT1)));
    else
        return (0);
}

t_ex_ret	loop_through_archive(t_bin_file *file, struct ar_hdr *object_header)
{
	char				*object_name;
	void				*object_ptr;
	uint32_t			object_size;

	while (object_header)
	{
		object_name = (char*)(object_header + 1);
		object_ptr = object_name + ft_padding_ar_mac(object_header->ar_name);
		object_size = ft_atoi(object_header->ar_size);
		if (!is_in_file(file, object_ptr, object_size - ft_padding_ar_mac(object_header->ar_name)))
			return (put_error(object_name, TRUNC_OBJECT));
		if (ft_nm(file->filename, object_name, object_size, object_ptr))
			return (FAILURE);
		object_header = (struct ar_hdr*)is_in_file(file, object_name \
			+ object_size, sizeof(*object_header));
	}
	return (SUCCESS);
}

t_ex_ret     handle_archive(char *filename, size_t size, void *ptr)
{
    struct ar_hdr       *header;
    unsigned int        symtab_size;
    struct ranlib       *symtab;
	unsigned int		string_table_size;
    struct ar_hdr       *object_header;
	t_bin_file			file;

	file.ptr = ptr;
	file.end = ptr + size;
	file.filename = filename;
    header = (struct ar_hdr*)(ptr + SARMAG);
    symtab_size = *(unsigned int*)((void*)(header + 1) \
		+ ft_padding_ar_mac(header->ar_name));
    symtab = (struct ranlib*) ((void*)(header + 1) \
		+ ft_padding_ar_mac(header->ar_name) + sizeof(unsigned int));
	string_table_size = *(unsigned int*)((void*)symtab + symtab_size);
    object_header = (struct ar_hdr*)is_in_file(&file, (void*)(header + 1) \
		+ ft_padding_ar_mac(header->ar_name) + sizeof(unsigned int) \
		+ symtab_size + sizeof(uint32_t) \
		+ string_table_size, sizeof(*object_header));
    return (loop_through_archive(&file, object_header));
}
