/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 13:34:36 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/03/27 18:10:02 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


char	flag(uint8_t n_type, uint8_t n_sect)
{
	ft_printf("\n%b\n", n_type);
	ft_printf("%b\n", n_sect);
	return (15);
}




void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int		i;
	struct	nlist_64 *el;
	char	*stringtable;

	el = (void*)ptr + symoff;
	stringtable = (void*)ptr +  stroff;
	i = 0;
	while (i < nsyms)
	{
		if (el[i].n_value != 0)
			ft_printf("%016zx ", el[i].n_value);
		else
			ft_printf("%17 ");
		ft_printf("%c", flag(el[i].n_type, el[i].n_sect));

	
		ft_printf("%s\n", stringtable + el[i].n_un.n_strx);
		i++;
	}
}

void	handler_64(char *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	int						ncmds;
	int						i;

	i = 0;
	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void*)(ptr + sizeof(struct mach_header_64));
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

void	nm(char *ptr)
{
	int		magic_number;

	magic_number = *((int*)ptr);
	if (magic_number == (int)MH_MAGIC_64)
		handler_64(ptr);
}

void	handler_nm(t_env *env)
{
	int		i;
	int		fd;
	struct stat buf;
	char	*ptr;

	i = 1;
	while (i < env->ac)
	{
		if (env->ac > 2)
			ft_printf("%s:\n", env->av[i]);
		if ((fd = open(env->av[i], O_RDONLY)) == -1)
			ft_printf("OPEN: Can Open this file sorry !\n");
		if (fstat(fd, &buf) == -1)
			ft_printf("%s\n", strerror(errno));
		if (buf.st_mode == S_IFDIR)
		if (env->ac > 2 && env->ac != i)
			ft_printf("\n");
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ft_printf("MAP FAILED");
		nm(ptr);
		if (munmap(ptr, buf.st_size)	 < 0)
			ft_printf("MUNMAP");
		i++;
	}
}

int main(int ac, char **av)
{
	t_env env;

	env.ac = ac;
	env.av = av;
	if (ac == 1)
	{
		// essaie a.out dans le dossier courant puis dans le dossier de nm
	}
	else
	{
		if (ac != 2)
			ft_printf("\n");
		handler_nm(&env);
	}
	return (EXIT_SUCCESS);
}
