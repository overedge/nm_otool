/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 22:20:22 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/03 18:55:20 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putstr_left(char *str, t_var *e)
{
	ft_putstr(str);
	e->ret += ft_strlen(str);
	ft_put_space(e->f_width - ft_strlen(str), e);
	free(str);
}

static void		ft_putstr_right(char *str, t_var *e)
{
	if (e->f_zero == 0)
		ft_put_space(e->f_width - ft_strlen(str), e);
	else
		ft_put_zero(e->f_width - ft_strlen(str), e);
	ft_putstr(str);
	e->ret += ft_strlen(str);
	free(str);
}

void			type_s(t_var *e)
{
	char *str;
	char *res;

	res = va_arg(e->ap, char*);
	if (res)
		str = ft_strdup(res);
	else if (!res && e->f_zero == 0)
	{
		ft_putstr("(null)");
		e->ret += 6;
		return ;
	}
	if (e->f_precis != 1)
		str = ft_strsub(str, 0, e->f_precis);
	if (e->f_width == 0)
	{
		ft_putstr(str);
		e->ret += ft_strlen(str);
		free(str);
		return ;
	}
	else if (e->f_width != 0 && e->f_left == 1)
		ft_putstr_left(str, e);
	else if (e->f_width != 0 && e->f_left == 0)
		ft_putstr_right(str, e);
}
