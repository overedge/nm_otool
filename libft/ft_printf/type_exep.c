/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_exep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:41:14 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/01/25 11:42:12 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putstr_left(t_var *e)
{
	ft_putchar('%');
	e->ret++;
	ft_put_space(e->f_width - 1, e);
}

static void		ft_putstr_right(t_var *e)
{
	if (e->f_zero == 0)
		ft_put_space(e->f_width - 1, e);
	else
		ft_put_zero(e->f_width - 1, e);
	ft_putchar('%');
	e->ret++;
}

void			type_exep(t_var *e)
{
	if (e->f_width == 0)
	{
		ft_putchar('%');
		e->ret++;
		return ;
	}
	else if (e->f_width != 0 && e->f_left == 1)
		ft_putstr_left(e);
	else if (e->f_width != 0 && e->f_left == 0)
		ft_putstr_right(e);
}
