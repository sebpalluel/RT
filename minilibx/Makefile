NOC			=	\033[0m
DEBC		=	\033[36m
OKC			=	\033[32m
ERC			=	\033[31m
WAC			=	\033[33m

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

all: $(NOM)
	@echo > /dev/null

debug: $(NOM)

$(NOM):	$(OBJ)
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	@rm -f $(NOM) $(OBJ) *~

fclean: clean
	@rm -f mlx_app

re: fclean all

.PHONY: all
