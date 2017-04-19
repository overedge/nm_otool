/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 01:06:47 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/19 02:54:41 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"


void	handler_lib(char *ptr)
{
	unsigned int size;
	

	

	while (ptr != NULL)
	{
		size = ft_atoi((char*)(ptr + 0x38));
		printf("%d\n", ft_atoi((char*)(ptr + 0x38)));
		ptr = (char*)ptr + size;
		printf("%s\n", (char*)(ptr + 0x80));
		nm(ptr + 0x94);
		if (size == 0)
			exit(1);
	}
}
