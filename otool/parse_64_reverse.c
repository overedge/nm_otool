/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:21:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/24 16:11:39 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_otool_64_reverse(struct section_64 *tet, unsigned int j,\
		char *ptr)
{
	uint64_t					i;
	uint64_t					size;
	unsigned char				*data;

	data = (unsigned char*)ptr + little_to_big_32_uint((tet + j)->offset);
	i = 0;
	ft_printf("%016llx\t", little_to_big_32_uint((tet + j)->addr));
	size = little_to_big_32_uint((tet + j)->size);
	while (i < size)
	{
		ft_printf("%02x", data[i]);
		i++;
		if (i % 4 == 0)
			ft_putchar(' ');
		if (i % 16 == 0 && i != size)
			ft_printf("\n%016llx\t",\
					little_to_big_32_uint((tet + j)->addr) + i);
	}
}

void	get_flag_64_reverse(struct load_command *lc, char *ptr)
{
	struct segment_command_64	*sas;
	struct section_64			*tet;
	unsigned int				j;

	sas = (struct segment_command_64*)lc;
	tet = (struct section_64 *)((char *)sas + \
			sizeof(struct segment_command_64));
	j = 0;
	while (j < little_to_big_32_uint(sas->nsects))
	{
		if (ft_strcmp((tet + j)->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_TEXT) == 0)
			print_otool_64_reverse(tet, j, ptr);
		j++;
	}
}

void	handler_64_reverse(char *ptr, char *argv)
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
	while (i < little_to_big_32_uint(header->ncmds))
	{
		if (little_to_big_32_uint(lc->cmd) == LC_SEGMENT_64)
			get_flag_64_reverse(lc, ptr);
		lc = (void*)lc + little_to_big_32_uint(lc->cmdsize);
		i++;
	}
	ft_putchar('\n');
}
