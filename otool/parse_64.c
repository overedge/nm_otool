/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:21:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/21 16:44:26 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		get_flag_64(struct load_command *lc, char *ptr)
{
	struct segment_command_64	*sas;
	struct section_64			*tet;
	unsigned int				j;
	uint64_t					size;
	uint64_t					i = 0;
	uint64_t					value;

	j = 0;
	sas = (struct segment_command_64*)lc;
	tet = (struct section_64 *)((char *)sas + \
			sizeof(struct segment_command_64));
	while (j < sas->nsects)
	{
		if (ft_strcmp((tet + j)->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_TEXT) == 0)
		{
			unsigned char *test = (unsigned char*)ptr + (tet + j)->offset;
			value = (tet + j)->addr;

			printf("%lld  ", value);
			size = (tet + j)->size;
			while (i < size)
			{
				ft_printf("%02x ", test[i]);
				i++;
			if (i % 16 == 0 || i == size)
				ft_printf("\n%017llx", &test[i]);
			}
		}
		j++;
	}
}


void		handler_64(char *ptr, char *argv)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	unsigned int			i;

	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(ptr + sizeof(struct mach_header_64));
	ft_printf("Contents of (__TEXT,__text) section\n");
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			get_flag_64(lc, ptr);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}
