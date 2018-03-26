/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:32:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/26 19:29:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "../libft/includes/libft.h"
# include "../includes/rtv1_define.h"

typedef struct		s_objsfunc
{
	size_t			(*builtinfunc)(void *a, t_list **list);
}					t_objsfunc;

typedef struct		s_mutex
{
	int var;
	pthread_mutex_t	mutex;
}					t_mutex;


typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef	struct		s_text
{
	t_col			*map;
	int				img_w;
	int				img_h;
}					t_text;

typedef	struct		s_text_c
{
	size_t			text_num;
	double			size_x;
	double			size_y;
}					t_text_c;

typedef	struct		s_gen
{
	size_t			mode;
	t_col			col;
	size_t			p_layers;
	double			p_f;
	double			p_prst;
}					t_gen;

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

typedef struct	s_cam
{
	t_vec3 org;
	t_vec3 frt;
	t_vec3 rgt;
	t_vec3 dwn;
	t_vec3 look_at;
	size_t	num_arg;
}				t_cam;

typedef struct	s_lgt
{
	size_t	type;
	t_vec3	vect;
	t_vec3 	dir;
	t_col	col;
	size_t	num_arg;
}				t_lgt;

typedef struct	s_sph
{
	t_vec3	ctr;
	double	r;
}				t_sph;

typedef struct	s_plan
{
	t_vec3	nrml;
	double	dst;
}				t_plan;

typedef struct	s_cone
{
	t_vec3	org;
	t_vec3	dir;
	double	theta;
}				t_cone;

typedef struct	s_cyl
{
	t_vec3	pos;
	t_vec3	dir;
	double	r;
}				t_cyl;

typedef struct	s_torus
{
	t_vec3		org;
	t_vec3		dir;
	double		s_r;
	double		b_r;
}				t_torus;

typedef struct	s_moebius
{
	t_vec3		org;
	t_vec3		axe_x;
	t_vec3		axe_y;
	double		r;
	double		width;
}				t_moebius;

typedef struct	s_shape
{
	int			type;
	size_t		num_arg;
	t_mat		mat;
	t_sph		sph;
	t_plan		plan;
	t_cone		cone;
	t_cyl		cyl;
	t_torus		tor;
	t_moebius	moeb;
}				t_shape;

typedef struct	s_ray
{
	t_vec3		org;
	t_vec3		dir;
	double		dist;
	double		n;
	int			nbrefl;
	int			flag;
}				t_ray;


typedef t_col	(*t_func_col)();
typedef double	(*t_func_dble)();
typedef char	*(*t_name_obj)();
typedef size_t	(*t_parse_obj)();
typedef	t_vec3	(*t_func_vec3)();
typedef	double	(*t_effects)();
typedef	t_col	(*t_postproc)();
typedef t_vec3	(*t_func_uv_map)();
//////////TODO Eliot

typedef struct		s_scene
{
	size_t			width;
	size_t			height;
	size_t			num_arg;
	t_list			*env;
	t_list			*forms;
	t_list			*lgts;
	t_list			*cams;
	t_cam			*cur_cam;
	size_t			cam_n;
	size_t			num_cam;
	size_t			num_lgt;
	t_mlx			*win;
	t_img			**img;
	t_fd			fd;
	double			move_step;
	double			rot_step;
	size_t			refr_max;
	size_t			refl_max;
	double			amb_light;
	double			pers;
	double			expo;
	size_t			effect;
}					t_scene;

typedef struct		s_setup
{
	size_t			width;
	size_t			height;
	char			*path;
	t_bool			ui; // afficher ou nom GUI
	size_t			error; // output la string d'erreur (avec fonction usage())
	size_t			mode; // gere different etat du programme STATE_*
	int				ac;
	int				key;
	t_col			background;
	t_mlx			*ui_win;
	t_img			*ui_img;
	void			*mlx_ptr;
	t_scene			*scene;
	size_t			num_scn;
	size_t			scn_num;
	pthread_t		*thrd;
	t_mutex			mutex;
	t_objsfunc		*builtin; // ft_validfuncsptr, pointeur sur les fonctions d'alloc de chaque objet
	t_text			**textures;
	t_img			vid[360];
}					t_setup;

#endif
