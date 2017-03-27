/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 21:26:13 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/03/05 18:12:18 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_width(char *fmt, t_var *e)
{
	char	*str;
	int		i;

	i = e->i;
	if (fmt[e->i] == '*')
	{
		e->f_width = va_arg(e->ap, int);
		e->i++;
	}
	else if (ft_isdigit(fmt[e->i]))
	{
		while (ft_isdigit(fmt[e->i]))
			e->i++;
		str = ft_strsub(fmt, i, e->i);
		e->f_width = ft_atoi(str);
		free(str);
	}
	else
		e->f_width = 0;
	if (fmt[e->i] == '+')
	{
		e->f_positive = 1;
		e->i++;
	}
}
