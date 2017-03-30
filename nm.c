/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 13:34:36 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/03/30 15:40:40 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	nm(char *ptr)
{
	int		magic_number;

	magic_number = *((int*)ptr);
	if (magic_number == (int)MH_MAGIC_64)
		handler_64(ptr);
	else if (magic_number == (int)MH_MAGIC)
		handler_32(ptr);
	else if (magic_number == (int)FAT_MAGIC)
		handler_fat(ptr);
	else if (magic_number == (int)FAT_CIGAM)
		handler_fat(ptr);
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
