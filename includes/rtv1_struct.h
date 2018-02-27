/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:32:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 14:07:17 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "../libft/includes/libft.h"

typedef struct		s_objsfunc
{
	size_t			(*builtinfunc)(void *a, t_list **list);
}					t_objsfunc;

typedef struct		s_mutex
{
	int var;
	pthread_mutex_t	mutex;
}					t_mutex;

typedef struct		s_matrix
{
	int				i;
	int				j;
	double			**mat;
}					t_matrix;

typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct		s_mat
{
	t_col			col;
	double			diffuse;
	double			specular;
}					t_mat;

typedef struct		s_cam
{
	t_vec3			org;
	t_vec3			frt;
	t_vec3			rgt;
	t_vec3			dwn;
	t_vec3			look_at;
	size_t			num_arg;
}					t_cam;

typedef struct		s_lgt
{
	size_t			type;
	t_vec3			vect;
	t_col			col;
	size_t			num_arg;
}					t_lgt;

typedef struct		s_sph
{
	t_vec3			ctr;
	double			r;
}					t_sph;

typedef struct		s_plan
{
	t_vec3			nrml;
	t_vec3			pos;
}					t_plan;

typedef struct		s_cone
{
	t_vec3			org;
	t_vec3			dir;
	double			theta;
}					t_cone;

typedef struct		s_cldre
{
	t_vec3			pos;
	t_vec3			dir;
	double			r;
}					t_cldre;

typedef struct		s_forms
{
	int				type;
	size_t			num_arg;
	t_sph			sph;
	t_plan			plan;
	t_cone			cone;
	t_cldre			cldre;
	t_vec3			norm;
	t_mat mat;
}					t_forms;

typedef struct		s_ray
{
	t_vec3			org;
	t_vec3			dir;
	double			dist;
	int				forme;
	t_bool			hit;
}					t_ray;

typedef	struct	s_hit
{
	t_vec3	pos;
	t_vec3	nrml;
	t_col		col;
}	t_hit;

typedef t_vec3		(*t_func_nrml)();
typedef char		*(*t_name_obj)();
typedef size_t		(*t_parse_obj)();
typedef t_bool		(*t_param)();

typedef struct		s_scene
{
	size_t			width;
	size_t			height;
	size_t			num_arg;
	t_list			*env;
	t_list			*forms;
	t_list			*lgts;
	t_list			*cams;
	size_t			cam_n;
	size_t			num_cam;
	size_t			num_lgt;
	t_mlx			*win;
	t_img			*img;
	t_fd			fd;
	double			move_step;
	double			rot_step;
	size_t			refr_max;
	size_t			refl_max;
	double			amb_light;
}					t_scene;

typedef struct		s_setup
{
	size_t			width;
	size_t			height;
	char			*path;
	size_t			error;
	size_t			mode;
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
	double			**camToWorld;
}					t_setup;

#endif
