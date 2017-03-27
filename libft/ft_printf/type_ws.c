/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ws.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 18:54:03 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/03 18:54:29 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putwchar(wchar_t chr, t_var *e)
{
	if (chr <= 0x7F)
		ft_putchar_ret(chr, e);
	else if (chr <= 0x7FF)
	{
		ft_putchar_ret((chr >> 6) + 0xC0, e);
		ft_putchar_ret((chr & 0x3F) + 0x80, e);
	}
	else if (chr <= 0xFFFF)
	{
		ft_putchar_ret((chr >> 12) + 0xE0, e);
		ft_putchar_ret(((chr >> 6) & 0x3F) + 0x80, e);
		ft_putchar_ret((chr & 0x3F) + 0x80, e);
	}
	else if (chr <= 0x1FFFFF)
	{
		ft_putchar_ret((chr >> 18) + 0xF0, e);
		ft_putchar_ret(((chr >> 12) & 0x3F) + 0x80, e);
		ft_putchar_ret(((chr >> 6) & 0x3F) + 0x80, e);
		ft_putchar_ret((chr & 0x3F) + 0x80, e);
	}
	else
		e->ret = -1;
}

void			ft_putwstr(wchar_t *str, t_var *e)
{
	while (*str)
		ft_putwchar(*str++, e);
}

wchar_t			*ft_strwsub(wchar_t *str, int start, int size)
{
	wchar_t *s;
	int		i;

	i = 0;
	s = (wchar_t*)malloc(sizeof(wchar_t) * size + 1);
	while (start < size)
	{
		s[i] = str[start];
		start++;
		i++;
	}
	s[size] = '\0';
	return (s);
}

int				ft_strwlen(wchar_t *str)
{
	int		i;

	i = 0;
	while (*str++)
	{
		if (*str <= 0x7FF)
			i += 1;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x1FFFFF)
			i += 4;
	}
	return (i);
}

void			type_ws(t_var *e)
{
	wchar_t *str;
	wchar_t *res;

	res = va_arg(e->ap, wchar_t*);
	if (e->f_zero == 1 && e->f_width != 0 && e->f_precis == 0)
		ft_put_zero(e->f_width, e);
	if (!res)
	{
		ft_putstr("(null)");
		e->ret += 6;
		return ;
	}
	if (e->f_zero == 1 && e->f_precis == 0)
		return ;
	str = res;
	if (e->f_precis > 1 && e->f_width > e->f_precis)
		str = ft_strwsub(str, 0, e->f_precis / 4);
	else if (e->f_precis > 1 && e->f_width < e->f_precis)
		str = ft_strwsub(str, 0, e->f_precis / 3);
	type_ws_2(e, str);
}
