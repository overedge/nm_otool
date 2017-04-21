/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:35:07 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/21 16:36:06 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		get_flag_32_reverse(t_compt *compteur, struct load_command *lc)
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


void		handler_32_reverse(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	unsigned int			i;
	t_compt					compteur;

	i = 0;
	header = (struct mach_header*)ptr;
	lc = (void*)(ptr + sizeof(struct mach_header));
	compteur.k = 0;
	while (i < little_to_big_32_uint(header->ncmds))
	{
		if (little_to_big_32_uint(lc->cmd) == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			break ;
		}
		if (little_to_big_32_uint(lc->cmd) == LC_SEGMENT)
			get_flag_32_reverse(&compteur, lc);
		lc = (void*)lc + little_to_big_32_uint(lc->cmdsize);
		i++;
	}
}
