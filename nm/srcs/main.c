#include "ft_nm.h"

t_symbol64    *create_symboles_table(size_t nb_symb) // dispensable ?
{
    t_symbol64     *symbols;
    
    if (!(symbols = (t_symbol64*)ft_memalloc(sizeof(t_symbol64) * nb_symb)))
    {
        return (NULL);
    }
    return (symbols);
}

char		get_type_char(struct nlist_64 *elem, void *ptr)
{
	(void)elem;
	(void)ptr;
	return ('X');
}

void        fill_symboles_table(struct symtab_command *symtab_cmd, t_symbol64 *symboles, void *ptr)
{
	size_t			i;
	char			*stringtable;
	struct nlist_64	*elem;

	elem = ptr + symtab_cmd->symoff;
	stringtable = ptr + symtab_cmd->stroff;

	i = 0;
	while (i < symtab_cmd->nsyms)
	{
        symboles[i].name = stringtable + elem[i].n_un.n_strx;
        symboles[i].type = elem[i].n_type;
		symboles[i].type_char = get_type_char(elem, ptr);
        i++;
	}
}

void        print_symboles_table(t_symbol64 *symboles, size_t nb_symb)
{
	size_t			i;

    i = 0;
	ft_putendl("=================================");
    while (i < nb_symb)
    {
		ft_putnbr(0);
		ft_putstr(" ");
		ft_putchar(symboles[i].type_char);
		ft_putstr(" ");
		ft_putendl(symboles[i].name);
        i++;
    }

}


t_ex_ret	handle_magic_64(size_t size, void *ptr)
{
	int						cmd_number;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*symtab_cmd;
    t_symbol64             *symboles;

    (void)size;
    (void)symboles;
	header = (struct mach_header_64 *)ptr;
	cmd_number = header->ncmds;

	lc = ptr + sizeof(*header);
	i = 0;
	while (i < cmd_number)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			puts("Section SYMTAB");
			symtab_cmd = (struct symtab_command *)lc;
			printf("nb symbols: %d\n", symtab_cmd->nsyms);
            if (!(symboles = create_symboles_table(symtab_cmd->nsyms)))
                return (FAILURE);
            fill_symboles_table(symtab_cmd, symboles, ptr);
            print_symboles_table(symboles, symtab_cmd->nsyms);
            free(symboles);
			return (SUCCESS);
		}
        i++;
		lc = (void *)lc + lc->cmdsize;
	}

    return (FAILURE);
}

t_ex_ret	ft_nm(size_t size, void *ptr)
{
    t_ex_ret        ret;
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
    ret = FAILURE;
	printf("magic number: %x\n", magic_number);

    if (magic_number == MH_MAGIC)
    {
		printf("MAGIC 32 bits\n");
	}
    else if (magic_number == MH_MAGIC_64)
	{
		printf("MAGIC 64 bits\n");
		ret = handle_magic_64(size, ptr);
	}
    else if (magic_number == MH_CIGAM)
    {
		printf("CIGAM 32 bits\n");
	}
    else if (magic_number == MH_CIGAM_64)
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
