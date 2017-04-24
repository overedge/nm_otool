/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 01:06:47 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:10:13 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	handler_lib(char *ptr, char *argv)
{
	unsigned int	size;

	size = ft_atoi((char*)(ptr + 0x38));
	ptr = (char*)((void*)ptr + size + 0x3C);
	while (ptr != NULL)
	{
		size = ft_atoi((char*)(ptr + 0x38));
		if (ft_strcmp("", (char*)(ptr + 0x44)) == 0)
			break ;
		ft_putchar('\n');
		ft_printf("%s(%s):\n", argv, (char*)(ptr + 0x44));
		if (ft_strlen((char*)(ptr + 0x44)) >= 19)
			otool((void*)(ptr + 0x60), argv);
		else if (ft_strlen((char*)(ptr + 0x44)) > 8)
			otool((void*)(ptr + 0x58), argv);
		else
			otool((void*)(ptr + 0x50), argv);
		ptr = (char*)((void*)ptr + size + 0x3C);
		if (size == 0)
			break ;
	}
}
