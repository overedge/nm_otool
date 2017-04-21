
all :
	@make -C nm/
	@make -C otool/
	@cp nm/ft_nm .
	@cp otool/ft_otool .
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DONE !\033[m"

debug :
	@make debug -C nm/
	@make debug -C otool/
	@cp nm/ft_nm .
	@cp otool/ft_otool .
	@echo "\033[1;31m --DEBUG--MODE-- :\033[m \033[1;32m DONE !\033[m"

clean :
	@make clean -C nm/
	@make clean -C otool/
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DELETE OBJ FILES !\033[m"

fclean : clean
	@rm -rf ft_nm
	@rm -rf ft_otool
	@make fclean -C nm/
	@make fclean -C otool/
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DELETE project !\033[m"

re : fclean all

.PHONY : all re clean fclean
