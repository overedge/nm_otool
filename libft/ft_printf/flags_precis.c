/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_precis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 21:35:34 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/03/05 18:14:58 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		precis_to_env(t_var *e, char *fmt, int i, char **str)
{
	e->i++;
	i = e->i;
	while (ft_isdigit(fmt[e->i]))
		e->i++;
	*str = ft_strsub(fmt, i, e->i);
	if (ft_atoi(*str) == 1)
	{
		e->f_precis = -1;
		free(*str);
	}
	else
	{
		e->f_precis = ft_atoi(*str);
		free(*str);
	}
}

void			flags_precis(char *fmt, t_var *e)
{
	char	*str;
	int		i;

	i = 0;
	if (fmt[e->i] == '.' && fmt[e->i + 1] == '0')
	{
		e->f_precis = 0;
		e->i += 2;
	}
	else if (fmt[e->i] == '.' && fmt[e->i + 1] == '*')
	{
		e->f_width = va_arg(e->ap, int);
		e->i += 2;
	}
	else if (fmt[e->i] == '.' && ft_isdigit(fmt[e->i + 1]))
		precis_to_env(e, fmt, i, &str);
	else if (fmt[e->i] == '.' && !ft_isdigit(fmt[e->i + 1]))
	{
		e->f_precis = 0;
		e->i++;
	}
	else
		e->f_precis = 1;
}
