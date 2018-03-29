/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:45:17 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 15:59:29 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** =============================================================================
** 							Includes
** =============================================================================
**
** kernal
** 		display_manager		Rendering scenes / Windows interactions
** 		graphical_manager	Post-proccess
** 		keys				Key handling
**
** Rest of the mess
** 			is none of my buisness ♪♪♪
*/

# include "./kernal.h"
# include "./rtv1_struct.h"
# include "./display_manager.h"
# include "./graphical_manager.h"
# include "./keys.h"

/*
** =============================================================================
** 							Global defined
** =============================================================================
*/

# define VERSION		"2.0.0"
# define VERSION_NICK	"2"
# define NAME			"Raytracer v" VERSION
# define NICK			"Rtv" VERSION_NICK

/*
** =============================================================================
** 							Colors
** =============================================================================
*/

# define C_NRM			"\033[0m"

# define C_SUC			"\033[38;2;141;143;38m"
# define C_ERR			"\033[38;2;231;76;60m"
# define C_CODE			"\033[38;2;243;156;18m"
# define C_WRN			"\033[38;2;230;126;34m"
# define C_INF			"\033[38;2;243;156;18m"

# define C_RED			"\033[38;2;231;76;60m"
# define C_ORANGE		"\033[38;2;230;126;34m"
# define C_YELLOW		"\033[38;2;241;196;15m"
# define C_GREEN		"\033[38;2;46;204;113m"
# define C_TEAL			"\033[38;2;26;188;156m"
# define C_BLUE			"\033[38;2;52;152;219m"
# define C_PURPLE		"\033[38;2;155;89;182m"
# define C_PINK			"\033[38;2;236;64;122m"

# define C_WHITE		"\033[38;2;236;240;241m"
# define C_LGREY		"\033[38;2;189;195;199m"
# define C_MGREY		"\033[38;2;149;165;166m"
# define C_DGREY		"\033[38;2;127;140;141m"
# define C_BLACK		"\033[38;2;44;62;80m"

/*
** =============================================================================
** 							Debug messages
** =============================================================================
*/

# define HEADER			C_MGREY "[" C_GREEN C_NICK C_MGREY "] "
# define HD				HEADER

# define ERR_HEADER		HD " [" C_ERR "x" C_MGREY "] [" C_CODE code C_MGREY "] "
# define WRN_HEADER		HD " [" C_WRN "!" C_MGREY "] [" sev C_MGREY "] "
# define INF_HEADER		HD " [" C_INF "i" C_MGREY "] "

# define WRN_SEV_MINOR	C_YELLOW "Minor" C_NRM
# define WRN_SEV_MEDIUM	C_ORANGE "Unsafe" C_NRM
# define WRN_SEV_MAJOR	C_RED "Critical" C_NRM

# define STR_ERR(c, s)	ERR_HEADER(c) C_LGREY s "\n" C_NRM
# define STR_WRN(s, sv)	WRN_HEADER(sv) C_LGREY s "\n" C_NRM
# define STR_INF(s)		INF_HEADER C_LGREY s C_NRM "\n"

/*
** =============================================================================
** 							Shapes
** =============================================================================
*/

typedef struct		s_sph
{
	t_vec3			ctr;
	double			r;
}					t_sph;

typedef struct		s_plan
{
	t_vec3			nrml;
	double			dst;
}					t_plan;

typedef struct		s_cone
{
	t_vec3			org;
	t_vec3			dir;
	double			theta;
}					t_cone;

typedef struct		s_cyl
{
	t_vec3			pos;
	t_vec3			dir;
	double			r;
}					t_cyl;

typedef struct		s_torus
{
	t_vec3			org;
	t_vec3			dir;
	double			s_r;
	double			b_r;
}					t_torus;

typedef struct		s_moebius
{
	t_vec3			org;
	t_vec3			axe_x;
	t_vec3			axe_y;
	double			r;
	double			width;
}					t_moebius;

typedef struct		s_shape
{
	int				type;
	size_t			num_arg;
	t_mat			mat;
	t_sph			sph;
	t_plan			plan;
	t_cone			cone;
	t_cyl			cyl;
	t_torus			tor;
	t_moebius		moeb;
}					t_shape;

/*
** =============================================================================
** 							Utils
** =============================================================================
*/

typedef struct		s_mat
{
	t_col			col;
	double			refl;
	double			n;
	double			trsp;
	size_t			text_m;
	t_text_c		text_c;
	t_gen			gen;
}					t_mat;

typedef struct		s_lgt
{
	size_t			type;
	t_vec3			vect;
	t_vec3 			dir;
	t_col			col;
	size_t			num_arg;
}					t_lgt;

typedef struct		s_ray
{
	t_vec3			org;
	t_vec3			dir;
	double			dist;
	double			n;
	int				nbrefl;
	int				flag;
}					t_ray;

/*
** =============================================================================
** 							Function typedefs
** =============================================================================
*/

typedef t_col		(*t_func_col)();
typedef char		*(*t_name_obj)();
typedef size_t		(*t_parse_obj)();
typedef	t_vec3		(*t_func_vec3)();
typedef t_vec3		(*t_func_uv_map)();
typedef	double		(*t_effects)();
typedef	SDL_Surface	*(*t_postproc)();

#endif
