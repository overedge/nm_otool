/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:09:56 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/19 17:59:39 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

uint32_t little_to_big_32_uint(uint32_t a)
{
	uint32_t	b;

	b = ((a>>24)&0xff) |
		((a<<8)&0xff0000) |
		((a>>8)&0xff00) |
		((a<<24)&0xff000000); return (b); } 

uint8_t  byte_to_reverse(uint8_t a)
{
	uint8_t b;

	b = ((a * 0x0802LU & 0x22110LU) |
	(a * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
	return (b);
}

uint64_t swap_long(uint64_t a)
{
	uint64_t b;
 
	b = a;
	b = (b & 0x00000000FFFFFFFF) << 32 | (b & 0xFFFFFFFF00000000) >> 32;
	b = (b & 0x0000FFFF0000FFFF) << 16 | (b & 0xFFFF0000FFFF0000) >> 16;
	b = (b & 0x00FF00FF00FF00FF) << 8  | (b & 0xFF00FF00FF00FF00) >> 8;
	
	return (b);
}
