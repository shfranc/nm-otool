#include "ft_nm.h"

static uint32_t     ft_padding_ar_mac(char *ar_name)
{
    uint32_t     ar_name_size;

    if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
    {
        ar_name_size = (uint32_t)ft_atoi(ar_name + ft_strlen(AR_EFMT1));
        // printf("ar name size: %d\n", ar_name_size);
    }
    else
        ar_name_size = 0;
    return (ar_name_size);
}

t_ex_ret     handle_archive(char *filename, size_t size, void *ptr)
{
    struct ar_hdr       *header;
    unsigned int        symtab_size;
    struct ranlib       *symtab;
	unsigned int		string_table_size;
    struct ar_hdr       *object_header;
	char				*object_name;
	t_bin_file			file;

    (void)filename;
    (void)size;

    header = (struct ar_hdr*)(ptr + SARMAG);
    symtab_size = *(unsigned int*)((void*)(header + 1) + ft_padding_ar_mac(header->ar_name));
    symtab = (struct ranlib*) ((void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(unsigned int));

	string_table_size = *(unsigned int*)((void*)symtab + symtab_size);
	file.ptr = ptr;
	file.end = ptr + size;

    object_header = (struct ar_hdr*)is_in_file(&file, (void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(unsigned int) + symtab_size + sizeof(uint32_t) + string_table_size, sizeof(*object_header));
	object_name = (char*)(object_header + 1);

	while (object_header)
	{
		if (ft_nm(filename, (char*)(object_header + 1), ft_atoi(object_header->ar_size), (void*)(object_header + 1) + ft_padding_ar_mac(object_header->ar_name)))
			return (FAILURE);
		object_header = (struct ar_hdr*)is_in_file(&file, (void*)(object_header + 1) + ft_atoi(object_header->ar_size), sizeof(*object_header));
	}

    return (SUCCESS);
}
