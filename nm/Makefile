SRC_NAME = nm.c list.c parse_64.c parse_32.c fat.c conversion.c \
parse_32_reverse.c parse_64_reverse.c lib.c

NAME = "ft_nm"

OBJ_NAME = $(SRC_NAME:.c=.o)

all : $(NAME)

$(NAME) :
	@make fclean -C ../libft/ && make -C ../libft/
	@cp ../libft/libft.a .
	@gcc -c -Wall -Werror -Wextra $(SRC_NAME)
	@gcc $(OBJ_NAME) -o $(NAME) -L. -lft
	@echo "\033[1;34m --NM-- :\033[m \033[1;32m DONE !\033[m"

debug :
	@make fclean -C ../libft/ && make -C ../libft/
	@cp ../libft/libft.a .
	@gcc -g -c $(SRC_NAME)
	@gcc -o $(NAME) $(OBJ_NAME) -L. -lft
	@echo "\033[1;31m --DEBUG--MODE-- :\033[m \033[1;32m DONE !\033[m"

clean :
	@rm -rf $(OBJ_NAME)
	@rm -rf libft.a
	@make clean -C ../libft/
	@echo "\033[1;34m --NM-- :\033[m \033[1;32m DELETE OBJ FILES !\033[m"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ../libft/
	@echo "\033[1;34m --NM-- :\033[m \033[1;32m DELETE project !\033[m"

re : fclean all

.PHONY : all re clean fclean
