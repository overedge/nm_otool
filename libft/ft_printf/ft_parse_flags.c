/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:56:39 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 14:06:30 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_other_char(char *fmt, t_var *e)
{
	if (fmt[e->i] == 'b')
		type_b(e);
	else
	{
		if (e->f_left == 0 && e->f_width != 0 && e->f_zero == 0)
			ft_put_space(e->f_width - 1, e);
		else if (e->f_left == 0 && e->f_width != 0 && e->f_zero == 1)
			ft_put_zero(e->f_width - 1, e);
		ft_putchar_ret(fmt[e->i], e);
		if (e->f_left == 1 && e->f_width != 0)
			ft_put_space(e->f_width - 1, e);
	}
}

void	ft_check_type(char *fmt, t_var *e)
{
	if (fmt[e->i] == 'C' || (fmt[e->i] == 'c' && e->f_l == 1))
		type_wc(e);
	else if (fmt[e->i] == 'S' || (fmt[e->i] == 's' && e->f_l == 1))
		type_ws(e);
	else if (fmt[e->i] == 'c')
		type_c(e);
	else if (fmt[e->i] == 's')
		type_s(e);
	else if (fmt[e->i] == 'd' || fmt[e->i] == 'i' || fmt[e->i] == 'D')
		type_d(e);
	else if (fmt[e->i] == 'u' || fmt[e->i] == 'U')
		type_u(e);
	else if (fmt[e->i] == 'X')
		type_x(e, 0);
	else if (fmt[e->i] == 'x')
		type_x(e, 1);
	else if (fmt[e->i] == 'o' || fmt[e->i] == 'O')
		type_o(e);
	else if (fmt[e->i] == 'p')
		type_p(e);
	else if (fmt[e->i] == '%')
		type_exep(e);
	else
		type_other_char(fmt, e);
}

void	ft_parse_flags(char *fmt, t_var *e)
{
	ft_construct_struct(e);
	e->i++;
	if (fmt[e->i] == '#')
		flags_effect(fmt, e);
	flags_left(fmt, e);
	flags_positive(fmt, e);
	flags_effect(fmt, e);
	flags_zero(fmt, e);
	flags_space(fmt, e);
	flags_width(fmt, e);
	flags_precis(fmt, e);
	flags_h(fmt, e);
	if (e->error == 0)
	{
		if (fmt[e->i] == 'U' || fmt[e->i] == 'D' || fmt[e->i] == 'O')
			e->u_exep = 1;
		ft_check_type(fmt, e);
	}
}
