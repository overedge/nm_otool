/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 22:13:21 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/04/21 16:35:07 by nahmed-m         ###   ########.fr       */
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
** Handler 64
*/
void					otool(char *ptr, char *argv);
void					handler_64_reverse(char *ptr);
void					handler_64(char *ptr, char *argv);
void					print_output_64(struct symtab_command *sym, char *ptr,\
						t_compt *compteur);
/*
** Handler 32
*/
void					handler_32_reverse(char *ptr);
void					handler_32(char *ptr);
void					get_flag_32(t_compt *compteur, struct load_command *lc);
/*
** Handler Fat && lib
*/
void					handler_fat(char *ptr, char *argv);
void					handler_lib(char *ptr, char *argv);
/*
** Conversion & utils
*/
uint32_t				little_to_big_32_uint(uint32_t a);
void					ft_error(char *str_error);
void					delete_fat_list(t_fat_ptr **list);
#endif
