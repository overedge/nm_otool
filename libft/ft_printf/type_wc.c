/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_wc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:48:23 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 14:55:46 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

static void		ft_putwchar(wchar_t wc)
{
	if (wc <= 127)
		ft_putchar(wc);
	else if (wc <= 0x7FF)
	{
		ft_putchar((wc >> 6) + 0xC0);
		ft_putchar((wc & 0x3F) + 0x80);
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar((wc >> 12) + 0xE0);
		ft_putchar(((wc >> 6) & 0x3F) + 0x80);
		ft_putchar((wc & 0x3F) + 0x80);
	}
	else if (wc <= 0x1FFFFF)
	{
		ft_putchar((wc >> 18) + 0xF0);
		ft_putchar(((wc >> 12) & 0x3F) + 0x80);
		ft_putchar(((wc >> 6) & 0x3F) + 0x80);
		ft_putchar((wc & 0x3F) + 0x80);
	}
}

static void		ft_putstr_left(wchar_t str, t_var *e)
{
	ft_putwchar(str);
	ft_put_space(e->f_width - 1, e);
}

static void		ft_putstr_right(wchar_t str, t_var *e)
{
	if (e->f_zero == 0)
		ft_put_space(e->f_width - 1, e);
	else
		ft_put_zero(e->f_width - 1, e);
	ft_putwchar(str);
}

void			type_wc(t_var *e)
{
	wchar_t str;

	str = (wchar_t)va_arg(e->ap, wint_t);
	if (str <= 0x7F)
		e->ret += 1;
	else if (str <= 0x7FF)
		e->ret += 2;
	else if (str <= 0xFFFF)
		e->ret += 3;
	else if (str <= 0x10FFFF)
		e->ret += 4;
	if (e->f_width != 0 && e->f_left == 1)
		ft_putstr_left(str, e);
	else if (e->f_width != 0 && e->f_left == 0)
		ft_putstr_right(str, e);
	else
		ft_putwchar(str);
}
