/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:25:18 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 19:46:24 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../includes/rtv1_struct.h"
# include "../includes/rtv1_define.h"

int			usage(int mode);
int			ft_quit(t_setup *setup);
void		ft_start(t_setup *setup);
void		ft_mlx_control(t_setup *setup);
void		ft_mlx_control_key(t_setup *setup);
t_setup		*ft_setup_alloc(t_setup *setup); // tous les define sont juste des racourcis sur la structure setup
char		**ft_validobjs(void); // ce qui contient tous les types d'objet qu'on gere pour le parsing
//t_objsparam	*ft_objsparam(void);
t_list		*ft_searchenv(t_list *env, char *name);
t_list		*ft_envlist(char *file);
t_list		*ft_newform(void);
char		**ft_getenv(t_setup *setup);
t_list		*ft_newenv(char *name, char *value);
void		ft_editenv(t_list *env, char *name, char *value);
size_t		ft_args_to_fd(t_setup *setup);
char		*ft_getobjstr(char *str, char *obj, int num);
t_list		*ft_parse_scn(t_setup *setup, char *file);
void		ft_getengine(t_list **env, char *eng_str);
void		ft_getcams(t_list **env, char *cam_str);
void		ft_getobjects(t_list **env, char *obj_str);
void		ft_getlights(t_setup *setup, t_list **env, char *light_str);
int			ft_setup_menu(t_setup *setup);
size_t		ft_select_scene(t_setup *setup, int scene);
size_t		ft_open_scene(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
void		ft_mlx_process(t_setup *setup);
void		ft_put_pxl_to_img(t_setup *setup, t_vec3 pos, t_color *clr);
t_bool		ft_getvectfromenv(t_vect *vect, char *value);
t_bool		ft_getcolfromenv(t_col *col, char *value);
t_bool		ft_getdoublefromenv(double *val, char *value);
t_bool		ft_getsize_tfromenv(size_t *val, char *value);
t_bool		ft_checkifallset(t_bool *flag, size_t numvar);
size_t		ft_engine(t_list **list);
size_t		ft_cam(t_list **list);
size_t		ft_light(t_list **list);
size_t		ft_plane(t_list **list);
size_t		ft_sphere(t_list **list);
t_parse_obj	*parse_obj(void);
void		*ft_raytracing(void *a); // Nathan: en fait ici c est la fonction de render
int			ft_raytracing_thread(t_setup *setup);
void		ft_setup_cam(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
size_t		ft_getobjscount(t_setup *setup);
t_bool		ft_plane_param(void *a, t_ray ray, double *dist);
t_bool		ft_sphere_param2(void *a, t_ray ray, double *dist);
t_bool		ft_sphere_param(t_ray *ray, void *a, double *t);

// TODO Eliot functions
t_setup		*get_st(void);
int			coltoi(t_col col);
t_col		addcol(t_col col1, t_col col2);
t_col		mult_scale_col(double t, t_col col);
t_col		multcol(t_col col1, t_col col2);
t_col		init_col(double r, double g, double b, double s);
t_col		interpolcol(t_col col1, t_col col2, double t);
int			init_mat(t_matrix *mat, int i, int j);
void		add_mat(t_matrix *a, t_matrix *b);
t_matrix	*mult_mat(t_matrix a, t_matrix b);
void		scale_mat(double a, t_matrix *res);
t_vect		vect_dot(t_vect u, t_vect v);
t_matrix	rot_mat(t_vect v, double theta);
t_matrix	id_mat(void);
t_vect		mult_vect_mat(t_matrix a, t_vect b);
t_vect		rot_vect(t_vect v, double theta, t_vect axis);
t_vect		init_vect(double x, double y, double z);
void		vect_mat_mult(t_matrix a, t_vect *u);
t_vect		vect_scale(double a, t_vect v);
t_vect		vect_mult(t_vect u, t_vect v);
t_vect		vect_add(t_vect u, t_vect v);
t_ray		init_ray(t_vect org, t_vect dir);
t_vect		vect_sub(t_vect u, t_vect v);
double		norme_vect(t_vect u);
t_vect		normal_vect(t_vect u);
double		vect_mult_scale(t_vect u, t_vect v);
t_col		send_ray(t_ray ray, t_env *env);
///////////////////////
//int			ft_mouse_hook(int mousecode, int x, int y, t_setup *setup);
//int			ft_mouse_moove(int x, int y, t_setup *setup);
//int			ft_expose_hook(t_setup *setup);
//void		ft_print(t_setup *setup);
//void		ft_path_maker(t_setup *setup);
//int			ft_configure_dim(t_setup *setup);
//size_t		ft_name_input(t_setup *setup);
//size_t		ft_generate_map(t_setup *setup);
//void		ft_path_maker_dir(t_setup *setup);
//int			ft_sky_select(t_setup *setup);
//int			ft_select_color(t_setup *setup);
//int			ft_give_color(t_setup *setup, t_color *color, int alpha);
//void		ft_draw_vert_line(t_setup *setup, int posx, int len);

#endif
