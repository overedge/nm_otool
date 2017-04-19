/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 13:34:36 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/19 16:02:57 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


void	ft_error(char *str_error)
{
	ft_putstr_fd(str_error, 2);
	exit(EXIT_FAILURE);
}

void	nm(char *ptr, char *argv)
{
	int		magic_number;

	magic_number = *((int*)ptr);
	if (magic_number == (int)MH_MAGIC_64)
		handler_64(ptr);
	else if (magic_number == (int)MH_CIGAM_64)
		handler_64_reverse(ptr);
	else if (magic_number == (int)MH_MAGIC)
		handler_32(ptr);
	else if (magic_number == (int)MH_CIGAM)
		handler_32_reverse(ptr);
	else if (magic_number == (int)FAT_MAGIC)
		handler_fat(ptr, argv);
	else if (magic_number == (int)FAT_CIGAM)
		handler_fat(ptr, argv);
	else if (magic_number == (int)MN_LIB)
		handler_lib(ptr, argv);
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
			ft_error("OPEN: Can Open this file sorry !\n");
		if (fstat(fd, &buf) == -1)
			ft_error("FSTAT: Can Fstat this file sorry !\n");
			if (env->ac > 2 && env->ac != i)
				ft_printf("\n");
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ft_error("MAP FAILED\n");
		nm(ptr, env->av[i]);
		if (munmap(ptr, buf.st_size) < 0)
			ft_error("MUNMAP FAILED\n");
		if (close(fd) == -1)
		ft_error("Error with close fd\n");
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
		env.ac = 2;
		env.av[1] = strdup("a.out");
		handler_nm(&env);
		ft_strdel(&env.av[1]);
	}
	else
	{
		if (ac != 2)
			ft_printf("\n");
		handler_nm(&env);
	}
	return (EXIT_SUCCESS);
}
