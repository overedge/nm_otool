/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:09:56 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:10:43 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

uint32_t	little_to_big_32_uint(uint32_t a)
{
	uint32_t	b;

	b = ((a >> 24) & 0xff) |
		((a << 8) & 0xff0000) |
		((a >> 8) & 0xff00) |
		((a << 24) & 0xff000000);
	return (b);
}

void		delete_fat_list(t_fat_ptr **list)
{
	t_fat_ptr *freeme;

	while (*list)
	{
		freeme = *list;
		*list = (*list)->next;
		free(freeme);
	}
}
