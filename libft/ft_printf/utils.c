/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:10:03 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 13:54:38 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_space(int space, t_var *e)
{
	int		i;

	i = 0;
	while (i < space)
	{
		ft_putchar(' ');
		e->ret++;
		i++;
	}
}

void	ft_put_zero(int zero, t_var *e)
{
	int		i;

	i = 0;
	while (i < zero)
	{
		ft_putchar('0');
		e->ret++;
		i++;
	}
}

void	ft_construct_struct(t_var *e)
{
	e->error = 0;
	e->f_left = 0;
	e->f_positive = 0;
	e->f_effect = 0;
	e->f_zero = 0;
	e->f_space = 0;
	e->f_width = 0;
	e->f_precis = 1;
	e->t_size = 0;
	e->f_hh = 0;
	e->f_h = 0;
	e->f_ll = 0;
	e->f_l = 0;
	e->f_j = 0;
	e->f_z = 0;
	e->u_exep = 0;
}

long	ft_verif_exep(long value, t_var *e)
{
	if (e->u_exep == 0)
	{
		if (e->f_hh == 1 && value < -128)
			value = 127;
		else if (e->f_hh == 1 && value > 127)
			value = -128;
		else if (e->f_h == 1 && value < -32768)
			value = 32767;
		else if (e->f_h == 1 && value > 32767)
			value = -32768;
	}
	if (value < -9223372036854775807)
	{
		e->error = 1;
		e->ret++;
		ft_putstr("-9223372036854775808");
	}
	return (value);
}

void	ft_putchar_ret(char c, t_var *e)
{
	ft_putchar(c);
	e->ret++;
}
