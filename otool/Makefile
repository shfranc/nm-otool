NAME = ft_otool
FLAGS = -Wall -Wextra -Werror
CC = gcc

LIB = libft.a
PATH_LIB = ../libft
PATH_SRCS = srcs
PATH_OBJS = objs

SRCS = $(addprefix $(PATH_SRCS)/, main.c \
	ft_otool.c \
	magic_64.c \
	magic_32.c \
	fat_32.c \
	fat_64.c \
	dump_hexa.c \
	archive.c \
	utils.c \
	utils_archive.c \
	utils_dump_hexa.c \
	error.c )
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
	@echo "$(GREEN)$@:$(RESET) OK"

$(PATH_LIB)/$(LIB):
	@make -C $(PATH_LIB)

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(INCS)
	@test -d $(PATH_OBJS) || mkdir $(PATH_OBJS)
	@$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I , $(INCS))
	@echo "$(YELLOW)compil:$(RESET) $@"

norm:
	@norminette $(PATH_SRCS) incs
	@make -C $(PATH_LIB) norm

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)
	@echo "$(BLUE)clean:$(RESET) $(PATH_OBJS)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)clean:$(RESET) $(NAME)"

fclean_lib:
	@make fclean -C $(PATH_LIB)

fclean_all: fclean_lib fclean

re_with_lib: fclean_all all

re: fclean all
