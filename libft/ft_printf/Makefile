# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 18:05:20 by nahmed-m          #+#    #+#              #
#*   Updated: 2016/02/01 02:35:20 by nahmed-m         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = ../libft.a


SRC_NAME = ft_printf.c ft_parse_flags.c flags_left.c flags_positive.c flags_effect.c flags_zero.c flags_space.c flags_width.c flags_precis.c flags_h.c type_d.c type_s.c type_c.c type_u.c type_x.c type_p.c type_o.c type_exep.c type_wc.c utils.c itoa_base.c type_ws.c type_b.c utils2.c

OBJ_NAME = $(SRC_NAME:.c=.o)


all :
	@gcc -Werror -Wextra -Wall $(SRC_NAME) -c
	@ar rc $(NAME) $(OBJ_NAME)
	@ranlib $(NAME)
	@echo "\033[1;34m ----PRINTF---- :\033[m \033[1;32m DONE !\033[m"

clean :
	@rm -rf $(OBJ_NAME)
	@echo "\033[1;34m ----PRINTF---- :\033[m \033[1;32m DELETE OBJ FILES !\033[m"

re : fclean all
