/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:31:26 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 19:58:54 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# include "../libft/includes/libft.h"

#define TRUE 1
#define FALSE 0 //parce que if FALSE -> pas execute

# define WIDTH			1280
# define HEIGHT			720
# define RATIO			WIDTH / HEIGHT
# define FOV        45
# define DEG2RAD(x)    ((x * M_PI) / 180)
# define MAX_SIZE		10000
# define MAX_OBJ		20
# define THREAD			4
# define NUM_OBJS		5
# define MAX_WINDOW		5
# define MAX_CAM		10
# define AMP			1.3

# define STATE_RUN		0
# define STATE_START	1
# define STATE_SELECT	2
# define STATE_SAVE		3
# define STATE_OPEN		4
# define STATE_DRAW		5
# define STATE_CAM		6
# define STATE_STOP		7

# define FILE_ERROR_S	"error: file doesn't exist or don't have the rights"
# define ENG_ERROR_S	"error: engine is not in the correct format"
# define LIGHT_ERROR_S	"error: light struct is not in the correct format"
# define PLANE_ERROR_S	"error: plane struct is not in the correct format"
# define SPHERE_ERROR_S	"error: sphere struct is not in the correct format"
# define CAM_ERROR_S	"error: cam struct is not in the correct format"
# define SCN_ERROR_S	"error: scene is not in the correct format"
# define OBJ_ERROR_S	"error: objects are not in the correct format"
# define DIM_ERROR_S	"error: dim is not in the correct format [100;4000]"
# define FILE_ERROR		-1
# define ENG_ERROR		-2
# define LIGHT_ERROR	-3
# define CAM_ERROR		-4
# define PLANE_ERROR	-5
# define SPHERE_ERROR	-6
# define SCN_ERROR		-7
# define OBJ_ERROR		-8
# define DIM_ERROR		-9

# define ENG_S			parsed[0]
# define CAM_S			parsed[1]
# define LGT_S			parsed[2]
# define OBJ_S			parsed[3]

# define UI_WIN			setup->ui_win
# define UI_IMG			setup->ui_img
# define NVARENG		5
# define SCN			setup->scene[setup->scn_num]
# define NVARCAM		2
# define NVARLIGHT		4
# define NVARPLANE		5
# define NVARSPHERE		5
# define CAM(x)			((t_cam *)(*(x)).content)
# define LGT(x)			((t_lgt *)(*(x)).content)
# define FORM(x)		((t_forms *)(*(x)).content)
# define SPHERE(x)		FORM(x)->sph
# define PLAN(x)		FORM(x)->plan
# define CONE(x)		FORM(x)->cone
//# define ENV(x)			((t_env *)(*(x)->env).content)
# define ENVSTRUCT(x)	((t_env *)(*(x)).content)

# define SPH			0
# define PLN			1
# define CON			2

# define MOVE_STEP		0.05
# define ROT_STEP		0.1

# define SCN_PATH_0		"scenes/scene_0.xml"
# define SCN_PATH_1		"scenes/scene_1.xml"
# define SCN_PATH_2		"scenes/"
# define SCN_PATH_3		"scenes/"
# define SCN_PATH_4		"scenes/"
# define SCN_PATH_5		"scenes/"

# define CHOOSE_STR		"To choose scene, press"
# define SELECT_STR		"0 || 1 || 2 || 3 || 4 || 5 || 6 || 7"
# define START_STR		"RTv1 by psebasti & nchalot"
# define ENTER_STR		"Press ENTER to start"

# define CAM_AV_STR		"Number of Camera available :"
# define CAM_CH_STR		"Choose the cam with number and press ENTER :"

# define GUI_M_STR		"|          GUI main menu          |"
# define GUI_M_SCN_STR	"|To change or select scene  :  S  |"
//# define RIGHT_STR		"Turn Right :  Right"
//# define PLUS_STR		"Speed Up   :  +"
//# define MINUS_STR		"Slow Down  :  -"
//# define GUI_STR		"Hide GUI   :  G"
//# define S_MODE_STR		"Change SKY :  1 2 3 4 5 6"
//# define ESC_STR		"Quit Game  :  Esc"

#endif
