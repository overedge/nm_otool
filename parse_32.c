/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:35:07 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/03/30 14:54:43 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	flag_32(uint8_t n_type, uint8_t n_sect, t_compt *compteur, uint64_t n_value)
{
	char		c;

	c = '?';
	if ((n_type & N_TYPE) == N_UNDF)
	{	
		c = 'u';
		if (n_value != 0)
			c = 'c';
	}
	if ((n_type & N_TYPE) == N_PBUD)
		c = 'u';
	else if ((n_type & N_TYPE) == N_SECT)
	{
		if (n_sect == compteur->text)
			c = 't';
		else if (n_sect == compteur->data)
			c = 'd';
		else if (n_sect == compteur->bss)
			c = 'b';
		else
			c = 's';
	}
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'i';
	if ((n_type & N_EXT) != 0 && c != '?')
		c = ft_toupper(c);
	return (c);
}

void		get_flag_32(t_compt *compteur, struct load_command *lc)
{
	struct segment_command  *sas;
	struct section *tet;

	sas = (struct segment_command*)lc;
	tet = (struct section*)((char *)sas + sizeof(struct segment_command));
	unsigned int j = 0;
	while (j < sas->nsects)
	{
		if(ft_strcmp((tet + j)->sectname, SECT_TEXT) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_TEXT) == 0)
			compteur->text = compteur->k + 1;
		else if(ft_strcmp((tet + j)->sectname, SECT_DATA) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_DATA) == 0)
			compteur->data = compteur->k + 1;
		else if(ft_strcmp((tet + j)->sectname, SECT_BSS) == 0 &&
				ft_strcmp((tet + j)->segname, SEG_DATA) == 0)
			compteur->bss = compteur->k + 1;
		j++;
		compteur->k++;
	}
}

void	print_output_32(struct symtab_command *sym, char *ptr, t_compt *compteur)
{
	unsigned int		i;
	struct	nlist *el;
	char	*stringtable;
	t_sort	*sort;
	char	c;

	sort = NULL;
	el = (void*)ptr + sym->symoff;
	stringtable = (void*)ptr +  sym->stroff;
	i = 0;
	while (i < sym->nsyms)
	{
		c = flag_32(el[i].n_type, el[i].n_sect, compteur, el[i].n_value);
		if (ft_strcmp(ft_strsub(stringtable + el[i].n_un.n_strx,  0, 7), "radr://"))
			add_list(el[i].n_value, c, stringtable + el[i].n_un.n_strx, &sort);
		i++;
	}
	sort_list(&sort);
	print_list(sort, 32);
}


void	handler_32(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	int						ncmds;
	int						i;
	t_compt compteur;
	i = 0;
	header = (struct mach_header*)ptr;
	ncmds = header->ncmds;
	lc = (void*)(ptr + sizeof(struct mach_header));
	compteur.k = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			print_output_32(sym, ptr, &compteur);
			break;
		}
		if (lc->cmd == LC_SEGMENT)
			get_flag_32(&compteur, lc);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}