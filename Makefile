
all :
	@make -C nm/
	@cp nm/ft_nm .
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DONE !\033[m"

debug :
	@make debug -C nm/
	@cp nm/ft_nm .
	@echo "\033[1;31m --DEBUG--MODE-- :\033[m \033[1;32m DONE !\033[m"

clean :
	@make clean -C nm/
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DELETE OBJ FILES !\033[m"

fclean : clean
	@rm -rf ft_nm
	@make fclean -C nm/
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DELETE project !\033[m"

re : fclean all

.PHONY : all re clean fclean
