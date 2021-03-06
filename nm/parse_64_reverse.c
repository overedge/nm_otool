/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:21:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/20 18:45:05 by nahmed-m         ###   ########.fr       */
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

void		print_output_64_reverse(struct symtab_command *sym, char *ptr,\
		t_compt *compteur)
{
	unsigned int		i;
	struct nlist_64		*el;
	char				*stringtable;
	t_sort				*sort;
	char				c;

	sort = NULL;
	el = (void*)ptr + little_to_big_32_uint(sym->symoff);
	stringtable = (void*)ptr + little_to_big_32_uint(sym->stroff);
	i = 0;
	while (i < little_to_big_32_uint(sym->nsyms))
	{
		c = flag(el[i].n_type, el[i].n_sect, compteur, el[i].n_value);
		if (ft_strcmp(stringtable + little_to_big_32_uint(el[i].n_un.n_strx),\
					"radr://5614542"))
			add_list(el[i].n_value, c, stringtable +\
					little_to_big_32_uint(el[i].n_un.n_strx), &sort);
		i++;
	}
	sort_list(&sort);
	print_list(sort, 1);
	del_list(&sort);
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
			print_output_64_reverse(sym, ptr, &compteur);
			break ;
		}
		if (little_to_big_32_uint(lc->cmd) == LC_SEGMENT_64)
			get_flag_64_reverse(&compteur, lc);
		lc = (void*)lc + little_to_big_32_uint(lc->cmdsize);
		i++;
	}
}
