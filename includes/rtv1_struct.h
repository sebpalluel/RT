/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:32:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/22 11:57:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "../libft/includes/libft.h"

typedef struct		s_objsfunc
{
	size_t			(*builtinfunc)(void *a, t_list **list);
}					t_objsfunc;

//typedef struct		s_ray
//{
//	double			size; // dist entre le point d'origine et l'objet touche le plus proche
//	t_bool			hit;
//	size_t			obj; // de quel type de forme il s'agit
//	size_t			objn; // l'index de l'objet (par exemple sphere[objn])
//	t_vec3			orig; // pos de la camera
//	t_vec3			dir;
//}					t_ray;
//
//typedef struct		s_objsparam
//{
//	// t_bool			(*paramfunc)(void *a, t_ray ray, double *dist);
//	t_bool			(*paramfunc)(t_ray ray, void *a, double *t);
//}					t_objsparam;

//typedef struct		s_env
//{
//	char			*name;
//	char			*value;
//}					t_env;
//
//typedef struct		s_mat
//{
//	t_color			col;
//	double			diffuse;
//	double			specular;
//}					t_mat;
//
//typedef struct		s_light
//{
//	size_t			type;
//	t_vec3			pos;
//	t_vec3			dir;
//	t_color			col;
//	double			intensity;
//	double			radius;
//	double			fallof;
//	double			focal_len;
//	size_t			num_arg;
//}					t_light;
//
//typedef struct		s_cam
//{
//	t_vec3			pos;
//	t_vec3			dir;
//	t_vec3			plane_center;
//	t_vec3			plane_dirX;
//	t_vec3			plane_dirY;
//	double			focal_len;
//	size_t			num_arg;
//}					t_cam;
//
//typedef struct		s_plane
//{
//	t_vec3			pos;
//	t_vec3			norm;
//	t_mat			mat;
//	size_t			num_arg;
//}					t_plane;
//
//typedef struct		s_sphere
//{
//	t_vec3			pos; // en fait c est le centre
//	t_mat			mat;
//	double			rad;
//	size_t			num_arg;
//}					t_sphere;
//
//typedef struct		s_objdef
//{
//	t_plane			*plane;
//	size_t			pl_n;
//	size_t			nplane;
//	t_sphere		*sphere;
//	size_t			sph_n;
//	size_t			nsphere;
//	size_t			objscount;
//}					t_objdef;
//
//typedef struct		s_objs // touts les types d'objets sont alloue sur MAX_OBJ = 20 (attention cas d'erreur a verifier si plus de 20 !)
//{
//	size_t			cam_n; // index de la cam
//	size_t			ncam; // nombre total de cam
//	t_light			*light; // Array de light
//	size_t			light_n; // index de la light
//	size_t			nlight; // nombre total de cam
//	t_objdef		objdef; // contient toutes les formes (sphere, cylindre, plan etc.)
//}					t_objs;

typedef struct		s_mutex
{
	int var;
	pthread_mutex_t	mutex;
}					t_mutex;

typedef struct	s_matrix
{
	int		i;
	int		j;
	double	**mat;
}				t_matrix;

//////////TODO Eliot

typedef struct	s_col
{
	double r;
	double g;
	double b;
	double s;
}				t_col;

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

typedef struct	s_cam
{
	t_vec3		org;
	t_vec3		frt;
	t_vec3		rgt;
	t_vec3		dwn;
	t_vec3		look_at;
	double		**camToWorld;
	size_t		num_arg;
}				t_cam;

typedef struct	s_lgt
{
	size_t	type;
	t_vec3	vect;
	t_col	col;
	size_t	num_arg;
}				t_lgt;

typedef struct	s_sph
{
	t_vec3	ctr;
	double	r;
	t_mat	mat;
}				t_sph;

typedef struct	s_plan
{
	t_vec3	nrml;
	t_vec3	pos;
	//double	dst;
	t_mat	mat;
}				t_plan;

typedef struct	s_cone
{
	t_vec3	org;
	t_vec3	dir;
	double	theta;
	t_mat	mat;
}				t_cone;

typedef struct s_cldre
{
	t_vec3	pos;
	t_vec3	dir;
	double	r;
	t_mat		mat;
}					t_cldre;

typedef struct	s_forms
{
	int						type;
	size_t				num_arg;
	t_sph					sph;
	t_plan				plan;
	t_cone				cone;
	t_cldre				cldre;
	t_vec3				norm;
}						t_forms;

typedef struct	s_ray
{
	t_vec3	org;
	t_vec3	dir;
	double	dist;
	int		forme;
	t_bool hit;
}				t_ray;

typedef t_col	(*t_func_col)();
typedef double	(*t_func_double)();
typedef char	*(*t_name_obj)();
typedef size_t	(*t_parse_obj)();
typedef t_bool	(*t_param)();
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
	double			**camToWorld;
	t_objsfunc		*builtin; // ft_validfuncsptr, pointeur sur les fonctions d'alloc de chaque objet
}					t_setup;

#endif
