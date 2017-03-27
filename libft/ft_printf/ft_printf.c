/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:07:08 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/01/27 16:19:13 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_printf(char *fmt, ...)
{
	t_var e;

	e.i = 0;
	e.ret = 0;
	if (fmt)
		va_start(e.ap, fmt);
	while (fmt[e.i] && fmt)
	{
		e.error = 0;
		if (fmt[e.i] == '%' && fmt[e.i + 1] != '\0')
			ft_parse_flags(fmt, &e);
		else if (e.error != 0)
			e.ret--;
		else if (fmt[e.i] == '%' && fmt[e.i + 1] == '\0')
			e.ret = e.ret;
		else
			ft_putchar_ret(fmt[e.i], &e);
		e.i++;
	}
	va_end(e.ap);
	return (e.ret);
}
