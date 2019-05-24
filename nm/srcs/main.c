#include "ft_nm.h"

static t_ex_ret	ft_nm(char *filename, size_t size, void *ptr)
{
    t_ex_ret        ret;
	uint32_t				magic_number;

	magic_number = *(uint32_t *)ptr;
    ret = FAILURE;
	printf("magic number: %x\n", magic_number);

    if (magic_number == MH_MAGIC)
    {
		printf("MAGIC 32 bits\n");
	}
    else if (magic_number == MH_MAGIC_64)
	{
		printf("MAGIC 64 bits\n");
		ret = handle_magic_64(filename, size, ptr);
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

	ret = ft_nm(av[1], buf.st_size, ptr);

	if (munmap(ptr, buf.st_size) < 0)
	{
		fprintf(stderr, "munmap: error\n");
		return (EXIT_FAILURE);
	}

    //close !!

	// while(1);
	return (EXIT_SUCCESS);
}
