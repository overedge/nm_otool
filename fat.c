/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:34:04 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/03/30 19:11:37 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"


void	handler_fat(char *ptr)
{
	struct	fat_header *header;
	struct	fat_arch *arch;
	int		i;

	header = (struct fat_header*)ptr;
	arch = (void*)(ptr + sizeof(struct fat_header));
	i = 0;
	ft_printf("%d\n", little_to_big_32(header->nfat_arch));
	while (i < (int)little_to_big_32(header->nfat_arch))
	{
		ft_printf("%d\n", little_to_big_32(arch->offset));
		ft_printf("%d\n-----------------\n", little_to_big_32(arch->size));
		arch = (void*)arch + sizeof(struct fat_arch);
		i++;
	}
}
