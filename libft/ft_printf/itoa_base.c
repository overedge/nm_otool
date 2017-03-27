/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 19:30:58 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/01/25 16:45:34 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_itoa_base(unsigned long value, unsigned long base, char up)
{
	unsigned long	i;
	unsigned long	j;
	char			*hex;
	char			*hex_low;

	hex = "0123456789ABCDEF";
	hex_low = "0123456789abcdef";
	j = 0;
	i = 1;
	while (value / i > base - 1)
		i *= base;
	while (i != 0)
	{
		if (up == 0)
			ft_putchar(hex[value / i]);
		else
			ft_putchar(hex_low[value / i]);
		value %= i;
		i /= base;
		j++;
	}
}

int		ft_itoa_count(unsigned long value, unsigned long base, t_var *e)
{
	unsigned long	i;
	unsigned long	j;
	int				c;

	c = 0;
	j = 0;
	i = 1;
	while (value / i > base - 1)
		i *= base;
	while (i != 0)
	{
		c++;
		value %= i;
		i /= base;
		j++;
		e->ret++;
	}
	return (c);
}
