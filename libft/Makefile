#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/10 23:29:24 by psebasti          #+#    #+#             *#
#*   Updated: 2018/03/21 17:49:59 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	=	libft.a

NOC			=	\033[0m
DEBC		=	\033[36m
OKC			=	\033[32m
ERC			=	\033[31m
WAC			=	\033[33m

SRCDIR = ./srcs/
OBJDIR = ./objs/
INCDIR = ./includes

STRPATH = str/
STDLIBPATH = stdlib/
CTYPEPATH = ctype/
LISTPATH = list/
PUTPATH = put/
MEMPATH = mem/
MATHPATH = math/
PERSOPATH = perso/
INTPATH = int/
TABPATH = tab/
PRINTPATH = print/
GFXPATH = gfx/
RANDPATH = rand/
FDPATH = fd/
ERRPATH = error/
MEMBLKPATH = memblock/
STRINGPATH = string/

SRC		=	$(MEMPATH)ft_memset.c\
			$(MEMPATH)ft_bzero.c\
			$(MEMPATH)ft_bzerotab.c\
			$(MEMPATH)ft_memcpy.c\
			$(MEMPATH)ft_memccpy.c\
			$(MEMPATH)ft_memmove.c\
			$(MEMPATH)ft_memchr.c\
			$(MEMPATH)ft_memcmp.c\
			$(MEMPATH)ft_memalloc.c\
			$(MEMPATH)ft_memdel.c\
			$(MEMPATH)ft_memdup.c\
			$(TABPATH)ft_tabfree.c\
			$(TABPATH)ft_h_flip.c\
			$(TABPATH)ft_v_flip.c\
			$(TABPATH)ft_tabnewsize_t.c\
			$(TABPATH)ft_tabnewint.c\
			$(TABPATH)ft_tabnewstr.c\
			$(TABPATH)ft_tab3newstr.c\
			$(TABPATH)ft_tab3free.c\
			$(TABPATH)ft_tabnullfree.c\
			$(TABPATH)ft_tabtostr.c\
			$(TABPATH)ft_tabdepth.c\
			$(TABPATH)ft_tablen.c\
			$(TABPATH)ft_tabstrcpy.c\
			$(TABPATH)ft_tabintcpy.c\
			$(STRPATH)ft_strlen.c\
			$(STRPATH)ft_strndup.c\
			$(STRPATH)ft_straddchar.c\
			$(STRPATH)ft_strdup.c\
			$(STRPATH)ft_strcpy.c\
			$(STRPATH)ft_strncpy.c\
			$(STRPATH)ft_strcat.c\
			$(STRPATH)ft_strncat.c\
			$(STRPATH)ft_strlcat.c\
			$(STRPATH)ft_strchr.c\
			$(STRPATH)ft_strrchr.c\
			$(STRPATH)ft_strstr.c\
			$(STRPATH)ft_strstrn.c\
			$(STRPATH)ft_strnstr.c\
			$(STRPATH)ft_strcmp.c\
			$(STRPATH)ft_strncmp.c\
			$(STRPATH)ft_strtrim.c\
			$(STRPATH)ft_striter.c\
			$(STRPATH)ft_striteri.c\
			$(STRPATH)ft_strmap.c\
			$(STRPATH)ft_strmapi.c\
			$(STRPATH)ft_strequ.c\
			$(STRPATH)ft_strnequ.c\
			$(STRPATH)ft_strsub.c\
			$(STRPATH)ft_strnew.c\
			$(STRPATH)ft_strjoin.c\
			$(STRPATH)ft_strjoinfree.c\
			$(STRPATH)ft_strnjoin.c\
			$(STRPATH)ft_strsplit.c\
			$(STRPATH)ft_strsplitequ.c\
			$(STRPATH)ft_strdel.c\
			$(STRPATH)ft_strclr.c\
			$(STRPATH)ft_strdup.c\
			$(STRPATH)ft_stroneof.c\
			$(STRPATH)ft_tolower.c\
			$(STRPATH)ft_toupper.c\
			$(INTPATH)ft_intmin.c\
			$(INTPATH)ft_intmax.c\
			$(INTPATH)ft_intdup.c\
			$(INTPATH)ft_getnbr.c\
			$(INTPATH)ft_intlen.c\
			$(CTYPEPATH)ft_isprint.c\
			$(CTYPEPATH)ft_isascii.c\
			$(CTYPEPATH)ft_isdigit.c\
			$(CTYPEPATH)ft_isalnum.c\
			$(CTYPEPATH)ft_isalpha.c\
			$(CTYPEPATH)ft_isspace.c\
			$(CTYPEPATH)ft_ishexa.c\
			$(CTYPEPATH)ft_isint.c\
			$(CTYPEPATH)ft_isfloat.c\
			$(CTYPEPATH)ft_issize_t.c\
			$(CTYPEPATH)ft_checkhexa.c\
			$(CTYPEPATH)ft_checkdigit.c\
			$(CTYPEPATH)ft_checkint.c\
			$(CTYPEPATH)ft_checkalnum.c\
			$(CTYPEPATH)ft_checkascii.c\
			$(PUTPATH)ft_putchar.c\
			$(PUTPATH)ft_putchar_fd.c\
			$(PUTPATH)ft_putstr.c\
			$(PUTPATH)ft_putstr_fd.c\
			$(PUTPATH)ft_putendl.c\
			$(PUTPATH)ft_putendl_fd.c\
			$(PUTPATH)ft_putnbr.c\
			$(PUTPATH)ft_putnbr_fd.c\
			$(STDLIBPATH)ft_atoi.c\
			$(STDLIBPATH)ft_atof.c\
			$(STDLIBPATH)ft_itoa.c\
			$(STDLIBPATH)ft_ftoa.c\
			$(STDLIBPATH)ft_strtol.c\
			$(STDLIBPATH)ft_stoul.c\
			$(MATHPATH)ft_sqrt.c\
			$(MATHPATH)ft_pow.c\
			$(MATHPATH)ft_floor.c\
			$(MATHPATH)ft_lerp.c\
			$(MATHPATH)ft_abs.c\
			$(MATHPATH)ft_range_num.c\
			$(LISTPATH)ft_lstnew.c\
			$(LISTPATH)ft_lstdelone.c\
			$(LISTPATH)ft_lstdelif.c\
			$(LISTPATH)ft_lstdel.c\
			$(LISTPATH)ft_lstadd.c	\
			$(LISTPATH)ft_lsttoarray.c\
			$(LISTPATH)ft_lstiter.c\
			$(LISTPATH)ft_lstmap.c\
			$(LISTPATH)ft_lstlen.c\
			$(LISTPATH)ft_lstaddend.c\
			$(LISTPATH)ft_lstaddfront.c\
			$(LISTPATH)ft_lstfree.c\
			$(LISTPATH)ft_lstpushback.c\
			$(LISTPATH)ft_lstpushfront.c\
			$(LISTPATH)ft_lstaddback.c\
			$(PERSOPATH)get_next_line.c\
			$(PERSOPATH)ft_swap.c\
			$(PERSOPATH)ft_perror.c\
			$(PERSOPATH)match.c\
			$(PERSOPATH)nmatch.c\
			$(PRINTPATH)ft_printfloatmatrix.c\
			$(PRINTPATH)ft_printintarray.c\
			$(PRINTPATH)ft_printsize_tarray.c\
			$(PRINTPATH)ft_printstrarray.c\
			$(GFXPATH)ft_colorcpy.c\
			$(GFXPATH)ft_color.c\
			$(GFXPATH)ft_colornew.c\
			$(GFXPATH)ft_colorparse.c\
			$(GFXPATH)ft_hextocolor.c\
			$(GFXPATH)ft_hexcolor.c\
			$(GFXPATH)ft_colortohex.c\
			$(GFXPATH)ft_coltoi.c\
			$(GFXPATH)ft_coladd.c\
			$(GFXPATH)ft_colmultscale.c\
			$(GFXPATH)ft_colmult.c\
			$(GFXPATH)ft_col_r.c\
			$(GFXPATH)ft_colinterpol.c\
			$(GFXPATH)ft_mlxdelete.c\
			$(GFXPATH)ft_imgclean.c\
			$(GFXPATH)ft_imgdel.c\
			$(GFXPATH)ft_imgnew.c\
			$(GFXPATH)ft_xmpnew.c\
			$(GFXPATH)ft_initwindow.c\
			$(GFXPATH)ft_matrixadd.c\
			$(GFXPATH)ft_matrixhomothety.c\
			$(GFXPATH)ft_matrixmult.c\
			$(GFXPATH)ft_matrixonpoint.c\
			$(GFXPATH)ft_matrixrotx.c\
			$(GFXPATH)ft_matrixroty.c\
			$(GFXPATH)ft_matrixrotz.c\
			$(GFXPATH)ft_matrixtranslate.c\
			$(GFXPATH)ft_matrixinit.c\
			$(GFXPATH)ft_pixcpy.c\
			$(GFXPATH)ft_pixnew.c\
			$(GFXPATH)ft_pixpopulate.c\
			$(GFXPATH)ft_vec3cpy.c\
			$(GFXPATH)ft_vec3new.c\
			$(GFXPATH)ft_vec3_r.c\
			$(GFXPATH)ft_vec3dot.c\
			$(GFXPATH)ft_vec3sub_r.c\
			$(GFXPATH)ft_vec3add_r.c\
			$(GFXPATH)ft_vec3mult_r.c\
			$(GFXPATH)ft_vec3div_r.c\
			$(GFXPATH)ft_vec3cross_r.c\
			$(GFXPATH)ft_vec3multscale_r.c\
			$(GFXPATH)ft_vec3addscale_r.c\
			$(GFXPATH)ft_vec3populate.c\
			$(GFXPATH)ft_vec3norm.c\
			$(GFXPATH)ft_vec3normalize.c\
			$(GFXPATH)ft_vec3normalize_r.c\
			$(GFXPATH)ft_vec3dist.c\
			$(GFXPATH)ft_vec3sop.c\
			$(GFXPATH)ft_vec3vop.c\
			$(GFXPATH)ft_vec3sop_r.c\
			$(GFXPATH)ft_vec3vop_r.c\
			$(GFXPATH)ft_vec3unit.c\
			$(GFXPATH)ft_vec3add3.c\
			$(GFXPATH)ft_dotproduct.c\
			$(GFXPATH)ft_sqrtf.c\
			$(GFXPATH)ft_invsqrt.c\
			$(GFXPATH)ft_mlx_keytoint.c\
			$(GFXPATH)ft_mlx_keytonumchar.c\
			$(GFXPATH)ft_mlx_keytoletterchar.c\
			$(GFXPATH)ft_mlx_printkeytochar.c\
			$(RANDPATH)ft_hash.c\
			$(RANDPATH)ft_hash32.c\
			$(RANDPATH)ft_rand.c\
			$(RANDPATH)ft_randint.c\
			$(RANDPATH)ft_random.c\
			$(RANDPATH)ft_randf.c\
			$(RANDPATH)ft_quintic.c\
			$(RANDPATH)ft_quinticderiv.c\
			$(RANDPATH)ft_lerp.c\
			$(RANDPATH)ft_rol.c\
			$(RANDPATH)ft_ror.c\
			$(FDPATH)ft_create_file.c\
			$(FDPATH)ft_open.c\
			$(FDPATH)ft_close.c\
			$(FDPATH)ft_fd_delete.c\
			$(ERRPATH)ft_error.c\
			$(ERRPATH)ft_error_exit.c\
			$(MEMBLKPATH)ft_mem_block.c\
			$(MEMBLKPATH)ft_mem_block_extension.c\
			$(MEMBLKPATH)ft_realloc.c\
			$(STRINGPATH)ft_t_string_concat.c\
			$(STRINGPATH)ft_t_string_concat_len.c\
			$(STRINGPATH)ft_t_string_expand.c\
			$(STRINGPATH)ft_t_string_new.c\

.PHONY: all build clean fclean re

OBJS 	=	$(SRCS:.c=.o)

CMP		=	gcc
FLAGS	=	-Wall -Wextra -Werror
DEBUG_F	=	-g3 -fsanitize=address

SRC := $(filter $(addprefix %, .c), $(SRC))
SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(SRC))))
OBJS_DIRS = $(sort $(dir $(OBJS)))

INCS_DIRS = $(addsuffix /, $(INCDIR))
INCS = $(addprefix -I, $(INCS_DIRS))

FAST_FLAG = -O3 -march=native -flto
SLOW_FLAG = -fsanitize=address -g3 -O0

EXT		=	Makefile

all: $(NAME) $(EXT)

debug: all

$(NAME): build $(LIBS) $(OBJS)
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	@echo "$(DEBC)$(NAME):\t$(NAME) DEBUG MODE$(NOC)"
endif
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\n$(OKC)$(NAME):\t$(NAME) READY$(NOC)"

build:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJS_DIRS)

clean:
	@rm -f $(LIBS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all


$(OBJDIR)%.o: $(SRCDIR)%.c
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	@$(CC) -c -o $@ $< $(INCS) $(FLAGS) $(SLOW_FLAG)
	@echo -n .
else
	@$(CC) -c -o $@ $< $(INCS) $(FLAGS) $(FAST_FLAG)
	@echo -n .
endif
