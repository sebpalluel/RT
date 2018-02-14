/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:32:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 13:59:54 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "../libft/includes/libft.h"

typedef struct		s_objsfunc
{
	size_t			(*builtinfunc)(void *a, t_list **list);
}					t_objsfunc;

typedef struct		s_ray
{
	double			size; // dist entre le point d'origine et l'objet touche le plus proche
	t_bool			hit;
	size_t			obj; // de quel type de forme il s'agit
	size_t			objn; // l'index de l'objet (par exemple sphere[objn]) 
	t_vec3			orig; // pos de la camera
	t_vec3			dir;
}					t_ray;

typedef struct		s_objsparam
{
	t_bool			(*paramfunc)(void *a, t_ray ray, double *dist);
}					t_objsparam;

typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct		s_mat
{
	t_color			col;
	double			diffuse;
	double			specular;
}					t_mat;

typedef struct		s_light
{
	size_t			type;
	t_vec3			pos;
	t_vec3			dir;
	t_color			col;
	double			intensity;
	double			radius;
	double			fallof;
	double			focal_len;
	size_t			num_arg;
}					t_light;

typedef struct		s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			plane_center;
	t_vec3			plane_dirX;
	t_vec3			plane_dirY;
	double			focal_len;
	size_t			num_arg;
}					t_cam;

typedef struct		s_plane
{
	t_vec3			pos;
	t_vec3			norm;
	t_mat			mat;
	size_t			num_arg;
}					t_plane;

typedef struct		s_sphere
{
	t_vec3			pos;
	t_mat			mat;
	double			rad;
	size_t			num_arg;
}					t_sphere;

typedef struct		s_objdef
{
	t_plane			*plane;
	size_t			pl_n;
	size_t			nplane;
	t_sphere		*sphere;
	size_t			sph_n;
	size_t			nsphere;
	size_t			objscount;
}					t_objdef;

typedef struct		s_objs // touts les types d'objets sont alloue sur MAX_OBJ = 20 (attention cas d'erreur a verifier si plus de 20 !)
{
	t_cam			*cam; // Array de cam
	size_t			cam_n; // index de la cam
	size_t			ncam; // nombre total de cam
	t_light			*light; // Array de light
	size_t			light_n; // index de la light
	size_t			nlight; // nombre total de cam
	t_objdef		objdef; // contient toutes les formes (sphere, cylindre, plan etc.)
	char			**validobjs; // valide que la struct est geree (cam, sphere etc.), avec ft_validobjs
	t_objsfunc		*builtin; // ft_validfuncsptr, pointeur sur les fonctions d'alloc de chaque objet
	t_objsparam		*param; // ft_objparam, pointeur sur fonction pour gerer les intersections de chaque objet 
}					t_objs;

typedef struct		s_setup
{
	size_t			width;
	size_t			height;
	size_t			refr_max;
	size_t			refl_max;
	double			amb_light;
	size_t			num_arg;
	t_bool			ui; // afficher ou nom GUI
	size_t			error; // output la string d'erreur (avec fonction usage())
	size_t			mode; // gere different etat du programme STATE_*
	size_t			cam_num;
	int				scn_num;
	double			move_step;
	double			rot_step;
	int				ac;
	char			*path;
	int				key;
	char			*str;
	t_mat			background;
	t_mlx			*mlx;
	t_img			*img;
	t_list			*env;
	t_objs			*objs; // ce qui contient tous les objets confondus (cam, light, forms)
	t_fd			*fd;
	pthread_t		*thrd;
}					t_setup;

#endif
