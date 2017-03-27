/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_postitive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 20:30:39 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/01 02:20:55 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_positive(char *fmt, t_var *e)
{
	if (fmt[e->i] == '+' && fmt[e->i + 1] == '\0')
		e->error = 1;
	else if (fmt[e->i] == '+')
	{
		while (fmt[e->i] == '+')
		{
			e->f_positive = 1;
			e->i++;
		}
	}
	else
		e->f_positive = 0;
}
