/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_h_l_L.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:26:39 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 01:55:22 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		verif_flags(char *fmt, t_var *e)
{
	if (fmt[e->i] == 'h' && fmt[e->i + 1] == 'h')
	{
		e->f_hh = 1;
		e->i++;
	}
	else if (fmt[e->i] == 'l' && fmt[e->i + 1] == 'l')
	{
		e->f_ll = 1;
		e->i++;
	}
	else if (fmt[e->i] == 'h')
		e->f_h = 1;
	else if (fmt[e->i] == 'l')
		e->f_l = 1;
	else if (fmt[e->i] == 'j')
		e->f_j = 1;
	else if (fmt[e->i] == 'z')
		e->f_z = 1;
}

void			flags_h(char *fmt, t_var *e)
{
	while (fmt[e->i] == 'h' || fmt[e->i] == 'l' || fmt[e->i] == 'j' ||
			fmt[e->i] == 'z')
	{
		if (fmt[e->i + 1] == '\0')
		{
			e->error = 1;
			return ;
		}
		else
			verif_flags(fmt, e);
		e->i++;
	}
	if (fmt[e->i] == '#')
		flags_effect(fmt, e);
}
