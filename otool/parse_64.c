/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:21:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:11:25 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_otool_64(struct section_64 *tet, unsigned int j, char *ptr)
{
	uint64_t					i;
	uint64_t					size;
	unsigned char				*data;

	data = (unsigned char*)ptr + (tet + j)->offset;
	i = 0;
	ft_printf("%016llx\t", (tet + j)->addr);
	size = (tet + j)->size;
	while (i < size)
	{
		ft_printf("%02x ", data[i]);
		i++;
		if (i % 16 == 0 && i != size)
			ft_printf("\n%016llx\t", (tet + j)->addr + i);
	}
}

void	get_flag_64(struct load_command *lc, char *ptr)
{
	struct segment_command_64	*sas;
	struct section_64			*tet;
	unsigned int				j;

	j = 0;
	sas = (struct segment_command_64*)lc;
	tet = (struct section_64 *)((char *)sas + \
			sizeof(struct segment_command_64));
	while (j < sas->nsects)
	{
		if (ft_strcmp((tet + j)->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_TEXT) == 0)
			print_otool_64(tet, j, ptr);
		j++;
	}
}

void	handler_64(char *ptr, char *argv)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	unsigned int			i;

	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(ptr + sizeof(struct mach_header_64));
	if (argv != NULL)
		ft_printf("%s:\nContents of (__TEXT,__text) section\n", argv);
	else
		ft_printf("\nContents of (__TEXT,__text) section\n");
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			get_flag_64(lc, ptr);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	ft_putchar('\n');
}
