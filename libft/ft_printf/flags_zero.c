/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 20:35:32 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 02:00:35 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_zero(char *fmt, t_var *e)
{
	if (fmt[e->i] == '0' && fmt[e->i + 1] == '\0')
		e->error = 1;
	else if (fmt[e->i] == '0')
	{
		while (fmt[e->i] == '0')
		{
			e->f_zero = 1;
			e->i++;
		}
	}
	else
		e->f_zero = 0;
	if (fmt[e->i] == '+')
		flags_positive(fmt, e);
	if (fmt[e->i] == '-')
		flags_left(fmt, e);
}
