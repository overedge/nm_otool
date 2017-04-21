/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:21:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/21 16:36:04 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		get_flag_64_reverse(t_compt *compteur, struct load_command *lc)
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
			compteur->text = compteur->k + 1;
		else if (ft_strcmp((tet + j)->sectname, SECT_DATA) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_DATA) == 0)
			compteur->data = compteur->k + 1;
		else if (ft_strcmp((tet + j)->sectname, SECT_BSS) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_DATA) == 0)
			compteur->bss = compteur->k + 1;
		j++;
		compteur->k++;
	}
}

void		handler_64_reverse(char *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	unsigned int			i;
	t_compt					compteur;

	i = 0;
	header = (struct mach_header_64*)ptr;
	lc = (void*)(ptr + sizeof(struct mach_header_64));
	compteur.k = 0;
	while (i < little_to_big_32_uint(header->ncmds))
	{
		if (little_to_big_32_uint(lc->cmd) == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			break ;
		}
		if (little_to_big_32_uint(lc->cmd) == LC_SEGMENT_64)
			get_flag_64_reverse(&compteur, lc);
		lc = (void*)lc + little_to_big_32_uint(lc->cmdsize);
		i++;
	}
}
