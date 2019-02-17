NAME=nm-otool

PATH_NM=nm/
NM=$(PATH_NM)ft_nm

PATH_OTOOL=otool/
OTOOL=$(PATH_OTOOL)ft_otool


PATH_LIB = libft/
LIBFT = $(PATH_LIB)/libft.a

all: $(LIBFT) $(NM) $(OTOOL)

$(LIBFT):
	@make -C $(PATH_LIB)

$(NM):
	@printf "\033[1;33m%s\033[0m\n" "============ NM ============="
	@make -C $(PATH_NM)

$(OTOOL):
	@printf "\033[1;33m%s\033[0m\n" "============ OTOOL =========="
	@make -C $(PATH_OTOOL)

run_tests:
	@make run_tests -C $(PATH_NM)
	@make run_tests -C $(PATH_OTOOL)

clean:
	@make -C $(PATH_NM) clean
	@make -C $(PATH_OTOOL) clean

fclean: clean
	@make -C $(PATH_NM) fclean
	@make -C $(PATH_OTOOL) fclean

fclean_lib :
	@make fclean -C $(PATH_LIB)

fclean_all : fclean_lib fclean

re_with_lib : fclean_all all	

re: fclean all