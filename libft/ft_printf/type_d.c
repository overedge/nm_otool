/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:42:26 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 15:57:05 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putstr_left(t_var *e, long value)
{
	if (value < 0)
		e->ret++;
	else if (e->f_positive == 1)
		ft_putchar_ret('+', e);
	else if (e->f_positive == 0 && e->f_space == 1)
		ft_putchar_ret(' ', e);
	if ((e->f_positive == 1 || e->f_space == 1) && e->f_precis != 1)
		e->f_precis++;
	if (value < 0 && e->f_precis != 1)
	{
		value *= -1;
		ft_putchar('-');
		e->f_precis++;
	}
	if (e->f_precis != 1 && e->f_width < e->f_precis)
		ft_put_zero(e->f_precis - e->t_size, e);
	else if (e->f_precis != 1 && e->f_width > e->f_precis)
		ft_put_zero(e->f_precis - e->t_size, e);
	ft_putnbr(value);
	if (e->f_left == 1 && e->f_width != 0 && e->f_width > e->t_size && \
			e->f_precis == 1)
		ft_put_space(e->f_width - e->t_size, e);
	else if (e->f_left == 1 && e->f_width != 0 && e->f_width > e->t_size\
			&& e->f_precis != 1)
		ft_put_space(e->f_width - e->f_precis, e);
}

static void		ft_putstr_right_next(t_var *e, long value)
{
	if ((e->f_zero == 1 || e->f_precis != 1) && value < 0)
	{
		ft_putchar_ret('-', e);
		if (e->f_precis != 1 && e->f_precis >= e->t_size && value < 0)
		{
			ft_put_zero(e->f_precis - e->t_size + 1, e);
			e->u_exep = 1;
		}
		value *= -1;
	}
	if (e->f_zero == 1 && e->f_precis == 1 && e->f_space == 1)
		ft_put_zero(e->f_width - e->t_size - 1, e);
	else if (e->f_zero == 1 && e->f_precis == 1)
		ft_put_zero(e->f_width - e->t_size, e);
	else if (e->f_precis != 1 && e->f_precis > e->t_size && value >= 0 && \
			e->u_exep != 1)
		ft_put_zero(e->f_precis - e->t_size, e);
	if (e->f_positive == 0 && e->f_space == 1 && e->f_precis == 0)
		ft_putchar_ret(' ', e);
	if (value < 0)
		e->ret++;
	ft_putnbr(value);
}

static void		ft_putstr_right(t_var *e, long value)
{
	if (e->f_zero == 1 && e->f_space == 1 && e->f_positive == 0 && value == 0)
		ft_put_space(1, e);
	else if ((e->f_zero == 0 && e->f_precis == 1) || (e->f_precis != 1 &&
					e->f_width > e->f_precis && e->f_precis < e->t_size))
		ft_put_space(e->f_width - e->t_size, e);
	else if (e->f_precis != 1 && e->f_width > e->f_precis && e->f_precis >\
			e->t_size)
		ft_put_space(e->f_width - e->f_precis - (value < 0 ? 1 : 0), e);
	else if (e->f_precis != 1 && e->f_width > e->f_precis && e->f_precis ==\
			e->t_size)
		ft_put_space(e->f_width - e->f_precis - 1, e);
	if (e->f_positive == 1)
		ft_putchar_ret('+', e);
	if (e->f_positive == 1 && e->f_precis != 1)
		e->f_precis++;
	ft_putstr_right_next(e, value);
}

static int		len_d(long value, t_var *e)
{
	int		i;

	i = 0;
	if (value < 0 && e->f_positive == 1)
		e->f_positive = 0;
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

void			type_d(t_var *e)
{
	long	value;

	if (e->f_hh == 1 && e->u_exep == 0)
		value = (char)va_arg(e->ap, int);
	else if (e->f_h == 0 && e->f_hh == 0 && e->f_ll == 0 && e->f_l == 0 \
			&& e->f_j == 0 && e->f_z == 0 && e->u_exep == 0)
		value = va_arg(e->ap, int);
	else
		value = va_arg(e->ap, long);
	if (e->f_precis == 0 && value == 0)
	{
		ft_put_space(e->f_width, e);
		return ;
	}
	value = ft_verif_exep(value, e);
	e->t_size = len_d(value, e);
	if (e->error == 1)
		return ;
	if (value < 0 || e->f_positive == 1 || (e->f_space == 1 && \
				e->f_positive == 1))
		e->t_size++;
	if (e->f_left == 0 && e->f_width != 0 && e->f_width > e->t_size)
		ft_putstr_right(e, value);
	else
		ft_putstr_left(e, value);
}
