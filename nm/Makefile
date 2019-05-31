NAME = ft_nm
FLAGS = -Wall -Wextra -Werror
CC = gcc

LIB = libft.a
PATH_LIB = ../libft
PATH_SRCS = srcs
PATH_OBJS = objs

SRCS = $(addprefix $(PATH_SRCS)/, main.c \
	macho_32.c \
	macho_64.c \
	fat_32.c \
	print.c \
	type.c \
	sort.c \
	check.c \
	error.c) 
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

clean_tests:
	@echo "cleaning old tests files..."
	@rm -f tests/input/*.output

run_tests: clean_tests
	@printf "\033[1;33m--------------------\n%s\n--------------------\033[0m\n" "$(NAME)"
	@python3 tests/main.py

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)
	@echo "$(BLUE)clean:$(RESET) $(PATH_OBJS)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)clean:$(RESET) $(NAME)"

fclean_lib :
	@make fclean -C $(PATH_LIB)

fclean_all: fclean_lib fclean

re_with_lib: fclean_all all	

re: fclean all
