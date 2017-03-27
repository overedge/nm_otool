/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:38:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/02 20:12:21 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putstr_left(t_var *e, unsigned long value, char up)
{
	if (e->f_width > e->t_size && e->f_precis < e->f_width)
		ft_put_space(e->f_width - e->t_size - 2, e);
	ft_putstr("0x");
	e->ret += 2;
	if (e->f_precis > e->t_size && e->f_precis > e->f_width)
		ft_put_zero(e->f_precis - e->t_size, e);
	ft_itoa_base(value, 16, up);
}

static void		ft_exep(t_var *e)
{
	if (e->f_left == 0 && e->f_width != 0 && e->f_zero == 0)
		ft_put_space(e->f_width - 3, e);
	ft_putstr("0x0");
	e->ret += 3;
	if (e->f_left == 1 && e->f_width != 0)
		ft_put_space(e->f_width - 3, e);
	if (e->f_zero == 1 && e->f_left == 0 && e->f_width != 0)
		ft_put_zero(e->f_width - 3, e);
}

void			type_p(t_var *e)
{
	unsigned long	value;

	value = va_arg(e->ap, unsigned long);
	if (value == 0 && e->f_precis == 0)
	{
		ft_putstr("0x");
		e->ret += 2;
		return ;
	}
	if (value == 0 && e->f_precis > 1)
	{
		ft_putstr("0x");
		e->ret += 2;
		ft_put_zero(e->f_precis, e);
		return ;
	}
	if (value == 0)
	{
		ft_exep(e);
		return ;
	}
	e->t_size = ft_itoa_count(value, 16, e);
	ft_putstr_left(e, value, 1);
}
