NAME = ft_nm
FLAGS = -Wall -Wextra -Werror
CC = gcc

LIB = libft.a
PATH_LIB = libft
PATH_SRCS = srcs
PATH_OBJS = objs

SRCS = $(addprefix $(PATH_SRCS)/, main.c \
	ft_nm.c \
	options.c )
OBJS = $(SRCS:$(PATH_SRCS)/%.c=$(PATH_OBJS)/%.o)
INCS = incs $(PATH_LIB)/includes

RED = \033[01;31m
GREEN = \033[01;32m
YELLOW = \033[01;33m
BLUE = \033[01;34m
PINK = \033[01;35m
CYAN = \033[01;36m
WHITE = \033[01;37m
RESET = \033[00m

all: $(NAME)

$(NAME): $(PATH_LIB)/$(LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)$@:$(RESET)\tOK"

$(LIB):
	@if [ ! -d $(PATH_LIB) ] ; then \
		git clone https://github.com/shfranc/libft $(PATH_LIB); \
	fi
	@make -C $(PATH_LIB)
	@echo "$(GREEN)libft : compilation OK$(RESET)"	

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(INCS)
	@test -d $(PATH_OBJS) || mkdir $(PATH_OBJS)
	@$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I , $(INCS))
	@echo "$(YELLOW)compil:$(RESET)\t$@"	

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)
	@echo "$(BLUE)clean:$(RESET)\t$(OBJS)"
	@# @make -C $(PATH_LIB) clean

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)clean:$(RESET)\t$(NAME)"
	@# @make -C $(PATH_LIB) fclean

re: fclean all

.PHONY: clean fclean re

	# gcc state.c -o state -I includes -L . -lft_malloc
