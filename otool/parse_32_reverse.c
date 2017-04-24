/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:35:07 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:11:10 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_otool_32_reverse(struct section *tet, unsigned int j, char *ptr)
{
	uint64_t					i;
	uint64_t					size;
	unsigned char				*data;

	data = (unsigned char*)ptr + little_to_big_32_uint((tet + j)->offset);
	i = 0;
	ft_printf("%08llx\t", little_to_big_32_uint((tet + j)->addr));
	size = little_to_big_32_uint((tet + j)->size);
	while (i < size)
	{
		ft_printf("%02x", data[i]);
		i++;
		if (i % 4 == 0)
			ft_putchar(' ');
		if (i % 16 == 0 && i != size)
			ft_printf("\n%08llx\t", \
					little_to_big_32_uint((tet + j)->addr) + i);
	}
}

void	get_flag_32_reverse(struct load_command *lc, char *ptr)
{
	struct segment_command	*sas;
	struct section			*tet;
	unsigned int			j;

	sas = (struct segment_command*)lc;
	tet = (struct section*)((char *)sas + sizeof(struct segment_command));
	j = 0;
	while (j < little_to_big_32_uint(sas->nsects))
	{
		if (ft_strcmp((tet + j)->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_TEXT) == 0)
			print_otool_32_reverse(tet, j, ptr);
		j++;
	}
}

void	handler_32_reverse(char *ptr, char *argv)
{
	struct mach_header		*header;
	struct load_command		*lc;
	unsigned int			i;

	i = 0;
	header = (struct mach_header*)ptr;
	lc = (void*)(ptr + sizeof(struct mach_header));
	if (argv != NULL)
		ft_printf("%s:\nContents of (__TEXT,__text) section\n", argv);
	else
		ft_printf("\nContents of (__TEXT,__text) section\n");
	while (i < little_to_big_32_uint(header->ncmds))
	{
		if (little_to_big_32_uint(lc->cmd) == LC_SEGMENT)
			get_flag_32_reverse(lc, ptr);
		lc = (void*)lc + little_to_big_32_uint(lc->cmdsize);
		i++;
	}
	ft_putchar('\n');
}
