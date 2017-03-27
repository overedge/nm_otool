/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:07:37 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/02/03 21:24:37 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include "../includes/libft.h"
# include <unistd.h>

typedef struct	s_var
{
	va_list ap;
	int		i;
	int		ret;
	char	error;
	char	f_left;
	char	f_positive;
	char	f_effect;
	char	f_zero;
	char	f_space;
	int		f_width;
	int		f_precis;
	char	f_hh;
	char	f_h;
	char	f_ll;
	char	f_l;
	char	f_j;
	char	f_z;
	int		t_size;
	char	u_exep;
}				t_var;

int				ft_printf(char *fmt, ...);

/*
** Flags Fuctions
*/
void			ft_parse_flags(char *fmt, t_var *e);
void			flags_left(char *fmt, t_var *e);
void			flags_positive(char *fmt, t_var *e);
void			flags_effect(char *fmt, t_var *e);
void			flags_zero(char *fmt, t_var *e);
void			flags_space(char *fmt, t_var *e);
void			flags_width(char *fmt, t_var *e);
void			flags_precis(char *fmt, t_var *e);
void			flags_h(char *fmt, t_var *e);

/*
** Type Fuctions
*/
void			ft_check_type(char *fmt, t_var *e);
void			type_d(t_var *e);
void			type_exep(t_var *e);
void			type_s(t_var *e);
void			type_c(t_var *e);
void			type_u(t_var *e);
void			type_x(t_var *e, char up);
void			type_o(t_var *e);
void			type_p(t_var *e);
void			type_wc(t_var *e);
void			type_ws(t_var *e);
void			type_ws_2(t_var *e, wchar_t *str);
void			type_b(t_var *e);
void			type_other_char(char *fmt, t_var *e);
/*
** Utils Fuctions
*/
void			ft_put_space(int space, t_var *e);
void			ft_put_zero(int zero, t_var *e);
void			ft_construct_struct(t_var *e);
long			ft_verif_exep(long value, t_var *e);
void			ft_putchar_ret(char c, t_var *e);
void			ft_itoa_base(unsigned long value, unsigned long base, char up);
int				ft_itoa_count \
				(unsigned long value, unsigned long base, t_var *e);
void			ft_putwstr(wchar_t *str, t_var *e);
int				ft_strwlen(wchar_t *str);
wchar_t			*ft_strwsub(wchar_t *str, int start, int size);
#endif
