#include "ft_nm.h"

t_symbol    *create_symbols_table(size_t nb_symb) // dispensable ?
{
    t_symbol     *symbols;
    
    if (!(symbols = (t_symbol*)ft_memalloc(sizeof(t_symbol) * nb_symb)))
    {
        return (NULL);
    }
    return (symbols);
}

char		get_type_char(uint8_t type, t_bin_file *file)
{
	uint8_t mask;
	unsigned char type_char;
	(void)file->ptr;
	printf("%d ", type);
	
	// debug, see stab.h afer
	if (type & N_STAB)
		return ('-');

	// limited global scope ??	
	if (type & N_PEXT)
		return ('?');
	
	// type of the symbol
	mask = type & N_TYPE;
	if (mask == N_UNDF)
	{
		printf("N_UNDF ");
		type_char = 'U';
	}
	if (mask == N_ABS)
	{
		printf("N_ABS ");
		type_char = 'A';
	}
	if (mask == N_PBUD)
	{
		printf("N_PBUD ");
		type_char = 'A';
	}
	if (mask == N_INDR)
	{
		printf("N_INDR ");
		type_char = '?'; // symbol is the same as another symbol, n_value field is an index into the string table specifying the name of the other symbol.
	}
	if (mask == N_SECT)
	{
		printf("N_SECT ");
		type_char = 'T'; // T ou D ou B
	}

	if (!(type & N_EXT)) // local symbol --> minuscule
		type_char ^= TOGGLE_CASE;
	printf("%c\n", type_char);
	return (type_char);
}

void        fill_symbols_table_64(t_bin_file *file)
{
	size_t			i;
	char			*stringtable;
	struct nlist_64	*elem;

	elem = file->ptr + file->symtab_cmd->symoff;
	stringtable = file->ptr + file->symtab_cmd->stroff;

	i = 0;
	while (i < file->symtab_cmd->nsyms)
	{
		file->symbols[i].addr = (void*)elem;
        file->symbols[i].name = stringtable + elem[i].n_un.n_strx;
		file->symbols[i].type = get_type_char(elem[i].n_type, file);
        i++;
	}
}

void        print_symbols_table(t_bin_file *file)
{
	size_t			i;

    i = 0;
	ft_putendl("=================================");
    while (i < file->symtab_cmd->nsyms)
    {
		ft_putnbr(0);
		ft_putstr(" ");
		ft_putchar(file->symbols[i].type);
		ft_putstr(" ");
		ft_putendl(file->symbols[i].name);
        i++;
    }

}


t_ex_ret	handle_magic_64(t_bin_file *file)
{
	int						cmd_number;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;

    (void)file->size;
	header = (struct mach_header_64 *)file->ptr;
	cmd_number = header->ncmds;

	lc = file->ptr + sizeof(*header);
	i = 0;
	while (i < cmd_number)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			puts("Section SYMTAB");
			file->symtab_cmd = (struct symtab_command *)lc;
			printf("nb symbols: %d\n", file->symtab_cmd->nsyms);
            if (!(file->symbols = create_symbols_table(file->symtab_cmd->nsyms)))
                return (FAILURE);
            fill_symbols_table_64(file);
            print_symbols_table(file);
            free(file->symbols);
			return (SUCCESS);
		}
        i++;
		lc = (void *)lc + lc->cmdsize;
	}

    return (FAILURE);
}

t_ex_ret	ft_nm(size_t size, void *ptr)
{
	t_bin_file		file;
    t_ex_ret        ret;


	file.ptr = ptr;
	file.size = size;
	file.magic_number = *(int *)ptr;
    ret = FAILURE;
	printf("magic number: %x\n", file.magic_number);

    if (file.magic_number == MH_MAGIC)
    {
		printf("MAGIC 32 bits\n");
	}
    else if (file.magic_number == MH_MAGIC_64)
	{
		printf("MAGIC 64 bits\n");
		ret = handle_magic_64(&file);
	}
    else if (file.magic_number == MH_CIGAM)
    {
		printf("CIGAM 32 bits\n");
	}
    else if (file.magic_number == MH_CIGAM_64)
    {
		printf("CIGAM 64 bits\n");
	}
    else
    {
        dprintf(2, "Wrong magic number\n");
    }

    return (ret);
}

int		main(int ac, char **av)
{
	int			fd;
	void		*ptr;
	struct stat buf;
    t_ex_ret        ret;

	ptr = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "usage: nm binary_file [...]\n");
		return (EXIT_FAILURE);
	}

	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		fprintf(stderr, "open: error\n");
		return (EXIT_FAILURE);
	}

	if ((fstat(fd, &buf)) < 0)
	{
		fprintf(stderr, "fstat: error\n");
		return (EXIT_FAILURE);
	}

	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap: error\n");
		return (EXIT_FAILURE);
	}

	ret = ft_nm(buf.st_size, ptr);

	if (munmap(ptr, buf.st_size) < 0)
	{
		fprintf(stderr, "munmap: error\n");
		return (EXIT_FAILURE);
	}

    //close !!

	return (EXIT_SUCCESS);
}
