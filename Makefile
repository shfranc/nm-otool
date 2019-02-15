NAME=nm-otool

all: $(NAME)

$(NAME):
	@echo "============ NM ============="
	@make -C nm
	@echo "============ OTOOL =========="
	@make -C otool

clean:
	@make -C nm clean
	@make -C otool clean

fclean: clean
	@make -C nm fclean
	@make -C otool fclean

re: fclean all

.PHONY: clean fclean re	
