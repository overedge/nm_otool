/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 18:39:32 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/03 18:53:20 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_ws_2(t_var *e, wchar_t *str)
{
	if (e->f_precis == 0)
	{
		ft_put_space(e->f_width, e);
		return ;
	}
	else if (e->f_precis == -1)
		str = ft_strwsub(str, 0, 1);
	if (e->f_width == 0)
	{
		ft_putwstr(str, e);
		return ;
	}
	else
	{
		if (e->f_zero == 1 && e->f_width != 0 && e->f_precis == 1)
			ft_put_zero(e->f_width - ft_strwlen(str) - 2, e);
		else if (e->f_width > ft_strwlen(str) && e->f_left == 0 && \
				e->f_precis != -1)
			ft_put_space(e->f_width - ft_strwlen(str) - 2, e);
		else if (e->f_precis == -1 && e->f_width > 1 && e->f_precis == -1)
			ft_put_space(e->f_width - 1, e);
		ft_putwstr(str, e);
		if (e->f_width > ft_strwlen(str) && e->f_left == 1)
			ft_put_space(e->f_width - ft_strwlen(str) - 2, e);
	}
}
