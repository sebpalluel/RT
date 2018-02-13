/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:31:26 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 18:44:57 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# include "../libft/includes/libft.h"

#define TRUE 1
#define FALSE 0 //parce que if FALSE -> pas execute

# define WIDTH			300
# define HEIGHT			300
# define RATIO			WIDTH / HEIGHT
# define FOV			(45 * M_PI) / 180
# define MAX_SIZE		10000
# define MAX_OBJ		20
# define NUM_THREAD		1
# define NUM_MAP		8
# define NUM_OBJS		4
# define AMP			1.3

# define STATE_RUN		0
# define STATE_START	1
# define STATE_SELECT	2
# define STATE_SAVE		3
# define STATE_OPEN		4
# define STATE_DRAW		5
# define STATE_CAM		6

# define FILE_ERROR_S	"error: file doesn't exist or don't have the rights"
# define MAP_ERROR_S	"error: map is not in the correct format"
# define LIGHT_ERROR_S	"error: light struct is not in the correct format"
# define PLANE_ERROR_S	"error: plane struct is not in the correct format"
# define SPHERE_ERROR_S	"error: sphere struct is not in the correct format"
# define CAM_ERROR_S	"error: cam struct is not in the correct format"
# define FILE_ERROR		-1
# define MAP_ERROR		-2
# define LIGHT_ERROR	-3
# define CAM_ERROR		-4
# define PLANE_ERROR	-5
# define SPHERE_ERROR	-6

# define SETUP			setup[0] // structure mere qui permet de stocker toutes les infos en commun sur chaque thread
# define S_WIDTH		setup[0].width
# define S_HEIGHT		setup[0].height
# define MLX			setup[0].mlx
# define IMG			setup[0].img
# define FD				setup[0].fd
# define RAY			setup[0].raytracer
# define OBJS			setup[0].objs
# define CAM			setup[0].objs->cam
# define NCAM			setup[0].objs->ncam
# define CAM_N			setup[0].cam_num
# define NVARCAM		2
# define LIGHT			setup[0].objs->light
# define NLIGHT			setup[0].objs->nlight
# define NVARLIGHT		3
# define OBJDEF			setup[0].objs->objdef
# define PLANE			setup[0].objs->objdef.plane
# define NPLANE			setup[0].objs->objdef.nplane
# define PL_N			setup[0].objs->objdef.pl_n
# define NVARPLANE		5
# define SPHERE			setup[0].objs->objdef.sphere
# define NSPHERE		setup[0].objs->objdef.nsphere
# define SPH_N			setup[0].objs->objdef.sph_n
# define NVARSPHERE		3
# define ENV(x)			((t_env *)(*(x)->env).content)
# define ENVSTRUCT(x)	((t_env *)(*(x)).content)

# define SPH			0
# define PLN			1

# define MOVE_STEP		0.05
# define ROT_STEP		0.1

# define MAP_PATH_0		"maps/map_0"
# define MAP_PATH_1		"maps/map_1"
# define MAP_PATH_2		"maps/"
# define MAP_PATH_3		"maps/"
# define MAP_PATH_4		"maps/"
# define MAP_PATH_5		"maps/"

# define CHOOSE_STR		"To choose map, press"
# define SELECT_STR		"0 || 1 || 2 || 3 || 4 || 5 || 6 || 7"
# define START_STR		"RTv1 by psebasti & nchalot"
# define ENTER_STR		"Press ENTER to start"

# define CAM_AV_STR		"Number of Camera available :"
# define CAM_CH_STR		"Choose the cam with number and press ENTER :"

# define DOWN_STR		"Backward   :  Down"
# define LEFT_STR		"Turn Left  :  Left"
# define RIGHT_STR		"Turn Right :  Right"
# define PLUS_STR		"Speed Up   :  +"
# define MINUS_STR		"Slow Down  :  -"
# define GUI_STR		"Hide GUI   :  G"
# define S_MODE_STR		"Change SKY :  1 2 3 4 5 6"
# define ESC_STR		"Quit Game  :  Esc"

#endif
