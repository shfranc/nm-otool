NAME = nm-otool

PATH_NM = nm/
NM = $(PATH_NM)ft_nm

PATH_OTOOL = otool/
OTOOL = $(PATH_OTOOL)ft_otool

GIT_LIB = https://github.com/shfranc/libft
PATH_LIB = libft/
LIBFT = $(PATH_LIB)/libft.a

YELLOW = \033[1;33m
RESET = \033[0m

all: $(LIBFT) $(NM) $(OTOOL)

$(LIBFT):
	@if [ ! -d $(PATH_LIB) ] ; then \
		git clone $(GIT_LIB) $(PATH_LIB); \
	fi
	@make -C $(PATH_LIB)

$(NM):
	@printf "$(YELLOW)%s$(RESET)\n" "============ NM ============="
	@make -C $(PATH_NM)

$(OTOOL):
	@printf "$(YELLOW)%s$(RESET)\n" "============ OTOOL =========="
	@make -C $(PATH_OTOOL)

clean_tests:
	@make clean_tests -C $(PATH_NM)
	@make clean_tests -C $(PATH_OTOOL)

run_tests:
	@make run_tests -C $(PATH_NM)
	@make run_tests -C $(PATH_OTOOL)

clean:
	@make -C $(PATH_NM) clean
	@make -C $(PATH_OTOOL) clean

fclean: clean
	@make -C $(PATH_NM) fclean
	@make -C $(PATH_OTOOL) fclean

fclean_lib:
	@make fclean -C $(PATH_LIB)

fclean_all: fclean_lib fclean

re_with_lib: fclean_all all	

re: fclean all
