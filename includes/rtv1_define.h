/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:31:26 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 19:06:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# include "../libft/includes/libft.h"


# define WIDTH			1280
# define HEIGHT			720
# define RATIO			WIDTH / HEIGHT
# define FOV			45
# define DEG2RAD(x)    ((x * M_PI) / 180)
# define THREAD			128
# define AMP			1.3

# define VIDEO_MODE		0

# define STATE_RUN		0
# define STATE_START	1
# define STATE_SELECT	2
# define STATE_SAVE		3
# define STATE_OPEN		4
# define STATE_DRAW		5
# define STATE_CAM		6
# define STATE_EFF		7
# define STATE_STOP		8

# define CIRCLE			PAS/PAS_TOTAL * (2 * M_PI)

# define UI_WIN			setup->ui_win
# define UI_IMG			setup->ui_img
# define CAM(x)			((t_cam *)(*(x)).content)
# define LGT(x)			((t_lgt *)(*(x)).content)
# define FORM(x)		((t_shape *)(*(x)).content)
# define SPHERE(x)		FORM(x)->sph
# define PLAN(x)		FORM(x)->plan
# define CONE(x)		FORM(x)->cone
# define CYLI(x)		FORM(x)->cyl
# define TORU(x)		FORM(x)->tor
# define MOEB(x)		FORM(x)->moeb

# define SPH			1
# define PLN			2
# define CON			3
# define CYL			4
# define TOR			5
# define MOE			6

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

# define EFF_AV_STR		"Effects available : Normal (0) | Sepia (1) | Cartoon (2) | Negative (3) | B&W (4) | Blur (5)"
# define EFF_CH_STR		"Choose the effect with number and press ENTER :"

# define GUI_M_STR		"|             GUI main menu          |"
# define GUI_M_SCN_STR	"|To change or select scene     :  S  |"
# define GUI_M_CAM_STR	"|To change or select cam       :  C  |"
# define GUI_M_EFF_STR	"|To choose an effect to apply  :  E  |"
//# define RIGHT_STR		"Turn Right :  Right"
//# define PLUS_STR		"Speed Up   :  +"
//# define MINUS_STR		"Slow Down  :  -"
//# define GUI_STR		"Hide GUI   :  G"
//# define S_MODE_STR		"Change SKY :  1 2 3 4 5 6"
//# define ESC_STR		"Quit Game  :  Esc"

#endif
