/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:35:07 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:10:57 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_otool_32(struct section *tet, unsigned int j, char *ptr)
{
	uint64_t					i;
	uint64_t					size;
	unsigned char				*data;

	data = (unsigned char*)ptr + (tet + j)->offset;
	i = 0;
	ft_printf("%08llx\t", (tet + j)->addr);
	size = (tet + j)->size;
	while (i < size)
	{
		ft_printf("%02x ", data[i]);
		i++;
		if (i % 16 == 0 && i != size)
			ft_printf("\n%08llx\t", (tet + j)->addr + i);
	}
}

void	get_flag_32(struct load_command *lc, char *ptr)
{
	struct segment_command	*sas;
	struct section			*tet;
	unsigned int			j;

	j = 0;
	sas = (struct segment_command*)lc;
	tet = (struct section*)((char *)sas + sizeof(struct segment_command));
	while (j < sas->nsects)
	{
		if (ft_strcmp((tet + j)->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_TEXT) == 0)
			print_otool_32(tet, j, ptr);
		j++;
	}
}

void	handler_32(char *ptr, char *argv)
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
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			get_flag_32(lc, ptr);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	ft_putchar('\n');
}
