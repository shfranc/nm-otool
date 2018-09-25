NAME=nm-otool

all: $(NAME)

$(NAME):
	@make -C nm
	@make -C otool

clean:
	@make -C nm clean
	@make -C otool clean

fclean: clean
	@make -C nm fclean
	@make -C otool fclean

re: fclean all

.PHONY: clean fclean re	