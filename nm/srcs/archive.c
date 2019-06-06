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
    // char                *long_name;
    unsigned int        symtab_size;
    unsigned int        nsyms;
    struct ranlib       *symtab;

    (void)filename;
    (void)size;

    header = (struct ar_hdr*)(ptr + SARMAG);
    // printf("sizeof ar_hdr: %lu\n", sizeof(struct ar_hdr));
    
    // write(1, "\n", 1);
    // write(1, header->ar_name, 16);
    // write(1, header->ar_date, 12);
    // write(1, "\n", 1);
    // write(1, header->ar_uid, 6);
    // write(1, "\n", 1);
    // write(1, header->ar_gid, 6);
    // write(1, "\n", 1);
    // write(1, header->ar_mode, 8);
    // write(1, "\n", 1);
    // write(1, header->ar_size, 10);
    // write(1, "\n", 1);
    // write(1, header->ar_fmag, 2);
    // write(1, "\n", 1);

    // long_name = (char*)(header + 1);
    // printf("longname: %s\n", long_name);

    symtab_size = *(unsigned int*)((void*)(header + 1) + ft_padding_ar_mac(header->ar_name));
    // printf("size of symble table: %d\n", symtab_size);

    nsyms = symtab_size / sizeof(struct ranlib);
    // printf("nb items: %d\n", nsyms);    

    symtab = (struct ranlib*) ((void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(unsigned int));
    // printf("ran_strx: %d\n", symtab->ran_un.ran_strx);
    // printf("ran_off: %u\n", symtab->ran_off);

	char 			*string_table;
	unsigned int	string_table_size;

	string_table_size = (unsigned int)((void*)symtab + symtab_size);
	string_table = (void*)symtab + symtab_size + sizeof(unsigned int);

    printf("symbol name: %s\n", string_table + symtab->ran_un.ran_strx);
	
    struct ar_hdr       *object_header;
	char				*object_name;
	void				*object_ptr;
	unsigned int		i;

	// object_header = (struct ar_hdr*)(ptr + symtab->ran_off);
    // object_name = (char*)(object_header + 1);
	// printf("object name: %s\n", object_name);
	
	// object_ptr = (void*)(object_header + 1) + ft_padding_ar_mac(object_header->ar_name);
	// ft_nm(filename, object_name, ft_atoi(object_header->ar_size), object_ptr);


	i = 0;
	while (i < nsyms)
	{
		object_header = (struct ar_hdr*)(ptr + symtab->ran_off);
    	object_name = (char*)(object_header + 1);
		object_ptr = (void*)(object_header + 1) + ft_padding_ar_mac(object_header->ar_name);
		if (ft_nm(filename, object_name, ft_atoi(object_header->ar_size), object_ptr) == FAILURE)
			return (FAILURE);
		i++;
		symtab++;
	}
    return (SUCCESS);
}
