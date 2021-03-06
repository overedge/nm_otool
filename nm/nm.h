/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 22:13:21 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/20 22:17:53 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <sys/stat.h>
# include <errno.h>
# include <mach-o/fat.h>
# include <unistd.h>
# include <ranlib.h>

# define MN_LIB 0x72613C21

typedef struct			s_env {
	int					ac;
	char				**av;
}						t_env;

typedef struct			s_compt {
	int					text;
	int					data;
	int					bss;
	int					k;
}						t_compt;

typedef struct			s_sort {
	unsigned long long	value;
	char				c;
	char				*str;
	struct s_sort		*next;
}						t_sort;

typedef struct			s_fat_ptr {
	void				*ptr;
	int					cputype;
	struct s_fat_ptr	*next;
}						t_fat_ptr;

/*
** List functions
*/
void					add_list(unsigned long long value, char c, char *str, \
						t_sort **list);
void					print_list(t_sort *list, int on);
void					sort_list(t_sort **list);
void					del_list(t_sort **list);
/*
** Handler 64
*/
void					nm(char *ptr, char *argv);
void					handler_64_reverse(char *ptr);
void					handler_64(char *ptr);
void					get_flag_64(t_compt *compteur, struct load_command *lc);
void					print_output_64(struct symtab_command *sym, char *ptr,\
						t_compt *compteur);
/*
** Handler 32
*/
void					handler_32_reverse(char *ptr);
void					handler_32(char *ptr);
void					get_flag_32(t_compt *compteur, struct load_command *lc);
void					print_output_32(struct symtab_command *sym, char *ptr,\
						t_compt *compteur);
/*
** Handler Fat && lib
*/
void					handler_fat(char *ptr, char *argv);
void					handler_lib(char *ptr, char *argv);
/*
** Conversion & utils
*/
uint32_t				little_to_big_32_uint(uint32_t a);
char					flag(uint8_t n_type, uint8_t n_sect, t_compt *compteur,\
						uint64_t n_value);
void					ft_error(char *str_error);
void					delete_fat_list(t_fat_ptr **list);
#endif
