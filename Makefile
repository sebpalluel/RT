# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 08:44:16 by mbeilles          #+#    #+#              #
#*   Updated: 2018/04/03 18:46:46 by psebasti         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#
#                                   Naming                                     #
#==============================================================================#

NAME = rt
NICK = "RTv2"

#==============================================================================#
#                                 Compilation                                  #
#==============================================================================#

FLAGS = $(HIDDEN_FLAGS) $(NAZI_FLAG)
CFLAG = -I$(PATH_INC) -I$(PATH_LIB)/$(PATH_INC) $(SDL_HDR_PATH) $(FLAGS)
FAST_FLAG = -O3 -march=native -flto
SLOW_FLAG = -fsanitize=address -g3 -O0

HIDDEN_FLAGS = #-v
NAZI_FLAG = #-Weverything

#==============================================================================#
#                                   Paths                                      #
#==============================================================================#

PATH_SRC = srcs
PATH_INC = includes
PATH_OBJ = obj
PATH_LIB = libft
PATH_MLX = minilibx

SDL_LIB_PATH = $(shell sdl2-config --libs)
SDL_HDR_PATH = $(shell sdl2-config --cflags)

VPATH = $(PATH_SRC):$(PATH_OBJ):$(PATH_INC)

#==============================================================================#
#                                   Various                                    #
#==============================================================================#

SHELL = /bin/sh
MAKE_DEP = 1
INSTALL_BREW = 0
INSTALL_SDL = 0
INSTALL_XML = 0

#==============================================================================#
#                                  Commands                                    #
#==============================================================================#

BREW_INSTALL_CMD = if [ -f $(HOME)/.brew ]; then printf $(HD)"Installing Brew\n"$(NRM) \
				   && curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

SDL_INSTALL_CMD = printf $(HD)"Installing SDL2\n"$(NRM) \
				  && brew install sdl2 \
				  && printf $(HD)"Installing SDL2_Ttf\n"$(NRM) \
				  && brew install sdl2_ttf

#==============================================================================#
#                                   Sources                                    #
#==============================================================================#

SRCS =	main.c																\
			setup.c															\
			setup_free.c													\
		mlx_process.c														\
		mlx_control.c														\
																			\
		light.c																\
																			\
		shape.c																\
			plane.c															\
			sphere.c														\
			cone.c															\
			moebius.c														\
			cylindre.c														\
																			\
		raytracing.c														\
			ray.c															\
				shadow.c													\
				reflexion.c													\
				diffuse.c													\
				noise.c														\
				perlin_calc.c												\
				postprocess.c												\
				postprocess2.c												\
				illumination.c												\
				newton.c													\
			raytracer_thread.c												\
			texture.c														\
				uv_maps.c													\
				uv_maps_helpers.c											\
																			\
		parser.c															\
			parser_torus_moebius.c											\
			parse_to_env_utils.c											\
			parser_error.c													\
			parser_utils.c													\
			parse_shape.c													\
			parse_objects.c													\
			open_scene.c													\
				env.c														\
				cam.c														\
				engine.c													\
																			\
		utils.c																\
			sp_mat.c														\
			matrices.c														\
			singleton.c														\
			singleton2.c													\
			save_img.c														\
#		draw.c																\
		raycaster.c															\

INC = libft.h																\
	  rtv1.h																\
	  rtv1_struct.h															\
	  rtv1_define.h															\
	  rtv1_global.h															\
	  matrice.h																\

DEPENDECIES = make -C $(PATH_LIB) $(INSTRUCTION) HIDDEN_FLAGS=$(HIDDEN_FLAGS);\
			  make -C $(PATH_MLX) $(INSTRUCTION) HIDDEN_FLAGS=$(HIDDEN_FLAGS);\

DEP = -L $(PATH_LIB) -lft													\
	  -L $(PATH_MLX) -lmlx													\
	  -framework OpenGL -framework Appkit									\
	  $(SDL_LIB_PATH) -lSDL2_image											\

#==============================================================================#
#                                    Vpaths                                    #
#==============================================================================#

vpath %.c $(PATH_SRC)/raytracing
vpath %.c $(PATH_SRC)/parser
vpath %.c $(PATH_SRC)/utils
vpath %.c $(PATH_SRC)/shapes
vpath %.c $(PATH_SRC)/mlx
vpath %.c $(PATH_SRC)
vpath %.o $(PATH_OBJ)
vpath %.h $(PATH_INC)
vpath %.h $(PATH_LIB)/$(PATH_INC)
vpath %.h $(PATH_MLX)

#==============================================================================#
#                             Variables Customizers                            #
#==============================================================================#

OBJS = $(SRCS:.c=.o)
ARG_O = $(addprefix $(PATH_OBJ)/,$(notdir $(SRCS:.c=.o)))

#==============================================================================#
#                                   Strings                                    #
#==============================================================================#

PROJECT_COLOR = "\033[38;2;254;128;25m"
PROJECT_COLOR_ALT = "\033[38;2;254;128;25m"
PRIMARY_COLOR = "\033[38;2;93;188;210m"
PRIMARY_COLOR_ALT = "\033[38;2;38;106;150m"
SUCCESS_COLOR = "\033[38;2;141;143;38m"
SUCCESS_COLOR_ALT = "\033[38;2;39;174;96m"
ERROR_COLOR = "\033[38;2;231;76;60m"
BOLD = "\033[1m"

KO = $(PRIMARY_COLOR_ALT)"["$(ERROR_COLOR)$(BOLD)" - "$(PRIMARY_COLOR_ALT)"] "
OK = $(PRIMARY_COLOR_ALT)"["$(SUCCESS_COLOR)$(BOLD)" + "$(PRIMARY_COLOR_ALT)"] "
HD = $(PRIMARY_COLOR_ALT)"["$(PROJECT_COLOR)$(NICK)$(PRIMARY_COLOR_ALT)"] "

NRM = "\033[0m"

SUCCESS_HD = $(PRIMARY_COLOR_ALT)"["$(PROJECT_COLOR)"SUCCESS"$(PRIMARY_COLOR_ALT)"] "
FAILURE_HD = $(PRIMARY_COLOR_ALT)"["$(PROJECT_COLOR)"FAILURE"$(PRIMARY_COLOR_ALT)"] "

MAKING_PROGRESS = $(OK)$(SUCCESS_COLOR_ALT)"> Genrating "$(NAME)"...\n"$(NRM)
MAKING_SUCCESS = $(SUCCESS_HD)$(SUCCESS_COLOR)$(NAME)" generated!\n"$(NRM)
MAKING_FAILURE = $(FAILURE_HD)$(ERROR_COLOR)$(NAME)" not generated!\n"$(NRM)

COMPILING_OK = $(HD)$(OK)$(PRIMARY_COLOR)"$@\n"$(NRM)
COMPILING_KO = $(HD)$(KO)$(ERROR_COLOR)"* "$(PRIMARY_COLOR)"$@\n"$(NRM)
COMPILING_DBG = $(HD)$(PROJECT_COLOR)$(NAME)" is compiling in "$(ERROR_COLOR)"debug"$(PROJECT_COLOR)" mode. \'make re\' to compile in production mode\n"$(NRM)
COMPILING_PRD = $(HD)$(PROJECT_COLOR)$(NAME)" is compiling in "$(SUCCESS_COLOR_ALT)"production"$(PROJECT_COLOR)" mode.\n"$(NRM)

COMPILED_DBG = $(SUCCESS_HD)$(PROJECT_COLOR)"Compiled with '"$(PRIMARY_COLOR)'$(strip "$(CFLAG) $(SLOW_FLAG)")'$(PROJECT_COLOR)"' flags.\n"$(NRM)
COMPILED_PRD = $(SUCCESS_HD)$(PROJECT_COLOR)"Compiled with '"$(PRIMARY_COLOR)'$(strip "$(CFLAG) $(FAST_FLAG)")'$(PROJECT_COLOR)"' flags.\n"$(NRM)

CLEANING_OBJS = $(HD)$(OK)$(PROJECT_COLOR)"Files cleaned\n"$(NRM)
CLEANING_BINS = $(HD)$(OK)$(PROJECT_COLOR)"Binary cleaned\n"$(NRM)

#==============================================================================#
#                                Os detection                                  #
#==============================================================================#
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CCFLAGS += -D LINUX
	CC := gcc
endif
ifeq ($(UNAME_S),Darwin)
	CCFLAGS += -D OSX
	CC := clang
endif
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
	CCFLAGS += -D AMD64
endif
ifneq ($(filter %86,$(UNAME_P)),)
	CCFLAGS += -D IA32
endif
ifneq ($(filter arm%,$(UNAME_P)),)
	CCFLAGS += -D ARM
endif
#==============================================================================#
#                                    Rules                                     #
#==============================================================================#


$(NAME): $(OBJS)
ifeq	(, $(filter debug, $(MAKECMDGOALS)))
	@$(eval INSTRUCTION := all)
	@if [ $(MAKE_DEP) == 1 ]; then $(DEPENDECIES) fi;
	@printf $(COMPILING_PRD)
	@$(CC) -o $(NAME) $(ARG_O) $(DEP) $(CFLAG) $(FAST_FLAG); \
		if [ $$? != 1 ]; then printf $(MAKING_SUCCESS); exit 0; \
		else printf $(MAKING_FAILURE); exit 2; fi
	@printf $(COMPILED_PRD)
else
	@$(eval INSTRUCTION := debug)
	@if [ $(MAKE_DEP) == 1 ]; then $(DEPENDECIES) fi;
	@printf $(COMPILING_DBG)
	@$(CC) -o $(NAME) $(ARG_O) $(DEP) $(CFLAG) $(SLOW_FLAG); \
		if [ $$? != 1 ]; then printf $(MAKING_SUCCESS); exit 0; \
		else printf $(MAKING_FAILURE); exit 2; fi
	@printf $(COMPILED_DBG)
endif

all: $(NAME)

debug: $(NAME)

%.o: %.c | $(PATH_OBJ)
ifeq	(,$(filter debug, $(MAKECMDGOALS)))
	@$(CC) -o $(PATH_OBJ)/$@ -c $< $(CFLAG) $(FAST_FLAG); \
		if [ $$? != 1 ]; then printf $(COMPILING_OK); exit 0; \
		else printf $(COMPILING_KO); exit 2; fi
else
	@$(CC) -o $(PATH_OBJ)/$@ -c $< $(CFLAG) $(SLOW_FLAG); \
		if [ $$? != 1 ]; then printf $(COMPILING_OK); exit 0; \
		else printf $(COMPILING_KO); exit 2; fi
endif

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)

install_dependencies: install_brew install_sdl
	@printf $(SUCCESS_HD)$(SUCCESS_COLOR)"Instalation complete!\n"

install_sdl:
	@$(SDL_INSTALL_CMD)

install_brew:
	@if [ ! -f $(HOME)/.brew ]; then
		$(BREW_INSTALL_CMD); fi

clean:
	@$(eval INSTRUCTION := clean)
	@if [ $(MAKE_DEP) == 1 ]; then $(DEPENDECIES) fi;
	@-rm -f $(ARG_O)
	@printf $(CLEANING_OBJS)

fclean:
	@$(eval INSTRUCTION := fclean)
	@if [ $(MAKE_DEP) == 1 ]; then $(DEPENDECIES) fi;
	@-rm -f $(ARG_O)
	@printf $(CLEANING_OBJS)
	@-rm -f $(NAME)
	@printf $(CLEANING_BINS)

re: fclean all

.PHONY: install_dependencies install_brew install_sdl clean fclean
