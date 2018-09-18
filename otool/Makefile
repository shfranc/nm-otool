NAME = ft_otool
FLAGS = -Wall -Wextra -Werror
CC = gcc

PATH_SRCS = srcs
PATH_OBJS = objs
PATH_INC = includes
SRCS = $(addprefix $(PATH_SRCS)/, test.c)
OBJS = $(SRCS:$(PATH_SRCS)/%.c=$(PATH_OBJS)/%.o)
INCS = $(addprefix $(PATH_INC)/, )

RED = \033[01;31m
GREEN = \033[01;32m
YELLOW = \033[01;33m
BLUE = \033[01;34m
PINK = \033[01;35m
CYAN = \033[01;36m
WHITE = \033[01;37m
RESET = \033[00m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)$@:$(RESET)\tOK"

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(INCS)
	@test -d $(PATH_OBJS) || mkdir $(PATH_OBJS)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(PATH_INC)
	@echo "$(YELLOW)compil:$(RESET)\t$@"	

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)
	@echo "$(BLUE)clean:$(RESET)\t$(OBJS)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)clean:$(RESET)\t$(NAME)"

re: fclean all

.PHONY: clean fclean re

	# gcc state.c -o state -I includes -L . -lft_malloc
