/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:33:25 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 14:11:13 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				ft_putnbr_u(unsigned long value)
{
	if (value >= 10)
		ft_putnbr_u(value / 10);
	ft_putchar(value % 10 + '0');
}

static void				ft_putstr_left(t_var *e, unsigned long value)
{
	if (e->f_precis != 1 && e->f_width < e->f_precis)
		ft_put_zero(e->f_precis - e->t_size, e);
	else if (e->f_precis != 1 && e->f_width > e->f_precis)
		ft_put_zero(e->f_precis - e->t_size, e);
	ft_putnbr_u(value);
	if (e->f_left == 1 && e->f_width != 0 && e->f_width > e->t_size && \
			e->f_precis == 1)
		ft_put_space(e->f_width - e->t_size, e);
	else if (e->f_left == 1 && e->f_width != 0 && e->f_width > e->t_size && \
			e->f_precis != 1)
		ft_put_space(e->f_width - e->f_precis, e);
}

static void				ft_putstr_right(t_var *e, unsigned long value)
{
	if (e->f_zero == 0 && e->f_precis == 1)
		ft_put_space(e->f_width - e->t_size, e);
	else if (e->f_precis != 1 && e->f_width > e->f_precis && e->f_precis >\
			e->t_size)
		ft_put_space(e->f_width - e->f_precis, e);
	else if (e->f_precis != 1 && e->f_width > e->f_precis && e->f_precis <\
			e->t_size)
		ft_put_space(e->f_width - e->t_size, e);
	if (e->f_zero == 1 && e->f_precis == 1)
		ft_put_zero(e->f_width - e->t_size, e);
	else if (e->f_precis != 1 && e->f_precis > e->t_size)
		ft_put_zero(e->f_precis - e->t_size, e);
	ft_putnbr_u(value);
}

static int				len_d(unsigned long value, t_var *e)
{
	int		i;

	i = 0;
	if (value == 0)
	{
		e->ret++;
		return (1);
	}
	while (value != 0)
	{
		i++;
		value /= 10;
	}
	e->ret += i;
	return (i);
}

void					type_u(t_var *e)
{
	unsigned long	value;

	if (e->f_hh == 1 && e->u_exep == 0)
		value = (unsigned char)va_arg(e->ap, unsigned int);
	else if (e->f_h == 0 && e->f_hh == 0 && e->f_ll == 0 && e->f_l == 0 && \
			e->f_j == 0 && e->f_z == 0 && e->u_exep == 0)
		value = va_arg(e->ap, unsigned int);
	else
		value = va_arg(e->ap, unsigned long);
	if (e->f_precis == 0 && value == 0)
	{
		ft_put_space(e->f_width, e);
		return ;
	}
	e->t_size = len_d(value, e);
	if (e->error == 1)
		return ;
	if (e->f_left == 0 && e->f_width != 0 && e->f_width > e->t_size)
		ft_putstr_right(e, value);
	else
		ft_putstr_left(e, value);
}
