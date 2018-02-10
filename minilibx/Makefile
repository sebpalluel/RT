#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/01/09 14:05:27 by psebasti          #+#    #+#             *#
#*   Updated: 2017/11/08 11:35:53 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME		=	wolf3d

NOC			=	\033[0m
DEBC		=	\033[36m
OKC			=	\033[32m
ERC			=	\033[31m
WAC			=	\033[33m

CMP			=	gcc

DEBUG_F		=	-g3 -fsanitize=address

FLAGS		=	-Wall -Wextra -Werror 

OBJDIR		=	./obj/
INCDIR		=	./includes/
SRCDIR		=	./srcs/

LFTDIR		=	./libft/
MLXDIR		=	./minilibx/
LIBS		=	-lft -lmlx -framework OpenGL -framework AppKit

OBJNAME		=	$(SRCNAME:.c=.o)
INCNAME		=	wolf3d.h \
				wolf3d_define.h \
				wolf3d_struct.h
SRCNAME 	=	wolf3d.c \
				setup.c \
				mlx_process.c \
				mlx_control.c \
				path_maker.c \
				path_maker_dir.c \
				configure_map.c \
				save_map.c \
				generate_map.c \
				open_map.c \
				draw.c \
				ray_casting.c \
				player.c \
				color.c \

SRC		= 	$(addprefix $(SRCDIR),$(SRCNAME))
OBJ		= 	$(addprefix $(OBJDIR),$(OBJNAME))
INC		= 	$(addprefix -I,$(INCDIR),$(INCNAME))

EXT			=	Makefile

debug : all

all: $(NAME) $(EXT)

$(NAME): $(OBJ)
	@echo
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	@echo "$(DEBC)$(NAME):\t\t$(NAME) DEBUG MODE$(NOC)"
	@echo "$(DEBC)IF YOU WANT TO SWITCH TO RELEASE VERSION 'make re'$(NOC)"
	@echo "$(DEBC)⤜(ʘvʘ)⤏$(NOC)"
	@make debug -C $(LFTDIR)
	@$(CMP) $(FLAGS) $(DEBUG_F) -o $(NAME) -L $(LFTDIR) -L $(MLXDIR) $(LIBS) $^ -o $@
else
	@make -C $(LFTDIR)
	@$(CMP) $(FLAGS) -o $(NAME) -L $(LFTDIR) -L $(MLXDIR) $(LIBS) $^ -o $@
	@echo "$(OKC)$(NAME):\t\t$(NAME) READY$(NOC)"
	@echo "$(OKC)¯\_ツ_/¯$(NOC)"
endif

$(OBJDIR)%.o: $(SRCDIR)%.c
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	@mkdir -p $(OBJDIR) 2> /dev/null || true
	@$(CMP) -c -o $@ $< $(INC) $(FLAGS) $(DEBUG_F)
	@echo -n .
else
	@mkdir -p $(OBJDIR) 2> /dev/null || true
	@$(CMP) -c -o $@ $< $(INC) $(FLAGS)
	@echo -n .
endif

clean:
	@make -C $(LFTDIR) clean
	@rm -rf $(OBJDIR)
	@echo "$(WAC)$(NAME):\t\tRemoving OBJ dir: ./obj/$(NOC)"

fclean: clean
	@make -C $(LFTDIR) fclean
	@rm -f $(NAME)
	@echo "$(WAC)$(NAME):\t\tRemoving $(NAME) executables$(NOC)"

re: fclean all

.PHONY: $(NAME) all clean fclean re
