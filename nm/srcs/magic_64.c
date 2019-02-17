#include "nm.h"

// void	print_output(int nsyms, int symoff, int stroff, void *ptr)
// {
// 	int				i;
// 	char			*stringtable;
// 	struct nlist_64	*elem;

// 	elem = ptr + symoff;
// 	stringtable = ptr + stroff;

// 	i = 0;
// 	while (i++ < nsyms)
// 	{
// 		if (elem[i].n_value)
// 			ft_puthexa(elem[i].n_value);
// 		else
// 			ft_putstr("                ");
// 		ft_putstr(" x ");
// 		ft_putendl(stringtable + elem[i].n_un.n_strx);		
// 	}
// }

t_symbole64			*ft_create_symbole(struct nlist_64 *symbole)
{
	t_symbole64		*elem;

	if (!(elem = (t_symbole64*)malloc(sizeof(t_symbole64))))
		ft_exit(ERR_MALLOC, MALLOC_FAILED); // No!!
	elem->symbole = symbole;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		ft_create_symboles_list(t_file64 *file)
{
	int				i;
	int				nb_syms;
	char			*stringtable;
	struct nlist_64	*symbole;	
	t_symbole64		*head;
	t_symbole64		*tmp;

	nb_syms = file->symtab_cmd->nsyms;
	stringtable = file->ptr + file->symtab_cmd->stroff;
	symbole = file->ptr + file->symtab_cmd->symoff;
	head = ft_create_symbole(symbole);
	tmp = head;
	i = 1;
	while (i++ < nb_syms)
	{
		ft_putendl(stringtable + symbole[i].n_un.n_strx); // segfault sur "64_exe_easy"
	}

}

void		ft_get_symtab_command(t_file64 *file)
{
    unsigned int            ncmds;
	struct load_command		*lc;
	unsigned int			i;

    ncmds = file->header->ncmds;
	lc = file->load_cmds;
    i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			file->symtab_cmd = (struct symtab_command *)lc;
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void		ft_init_struct_file(t_file64 **file, void *ptr)
{
	if (!(*file = (t_file64*)malloc(sizeof(t_file64))))
		ft_exit(ERR_MALLOC, MALLOC_FAILED); // NO!!
	ft_bzero(*file, sizeof(t_file64));
	(*file)->ptr = ptr;
	(*file)->header = (struct mach_header_64*)ptr;
	(*file)->load_cmds = (struct load_command*)((*file)->header + 1);
	ft_get_symtab_command(*file);
}

int		ft_handle_magic_64(void *ptr)
{
	t_file64	*file;

	ft_init_struct_file(&file, ptr);
	ft_create_symboles_list(file);

    return (EXIT_SUCCESS);
}

// int		ft_handle_magic_64(void *ptr)
// {
//     struct mach_header_64   *header;
//     unsigned int            ncmds;
// 	struct load_command		*lc;
//     struct symtab_command	*sym;
//     unsigned int			i;

//     header = (struct mach_header_64*)ptr;
//     ncmds = header->ncmds;
//     printf("nb cmd: %d\n", ncmds);

//     lc = (struct load_command*)(header + 1);
    
//     i = 0;
// 	while (i++ < ncmds)
// 	{
// 		if (lc->cmd == LC_SYMTAB)
// 		{
// 			puts("Section SYMTAB");
// 			sym = (struct symtab_command *)lc;
// 			printf("nb symbols: %d\n", sym->nsyms);
// 			print_output(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
// 			break ;
// 		}
// 		lc = (void *)lc + lc->cmdsize;
// 	}
//     return (0);
// }
