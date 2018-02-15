/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:25:18 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/15 16:52:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../includes/rtv1_struct.h"
# include "../includes/rtv1_define.h"

int			usage(int mode);
char		**ft_validobjs(void);
t_objsfunc	*ft_validfuncsptr(void);
t_objsparam	*ft_objsparam(void);
size_t		ft_cam(void *a, t_list **list);
t_list		*ft_searchenv(t_list *env, char *name);
t_list		*ft_envlist(char *file);
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
size_t		ft_setup_mode(t_setup *setup, size_t mode);
int			ft_setup_menu(t_setup *setup);
size_t		ft_select_scene(t_setup *setup);
size_t		ft_open_scene(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
void		ft_mlx_process(t_setup *setup);
void		ft_put_pxl_to_img(t_setup *setup, t_vec3 pos, t_color *clr);
t_bool		ft_getvec3fromenv(t_vec3 *vec3, char *value);
t_bool		ft_getcolfromenv(t_color *col, char *value);
t_bool		ft_getdoublefromenv(double *val, char *value);
t_bool		ft_getsize_tfromenv(size_t *val, char *value);
t_bool		ft_checkifallset(t_bool *flag, size_t numvar);
size_t		ft_engine(void *a, t_list **list);
size_t		ft_cam(void *a, t_list **list);
size_t		ft_light(void *a, t_list **list);
size_t		ft_plane(void *a, t_list **list);
size_t		ft_sphere(void *a, t_list **list);
void		*ft_raytracing(void *a); // Nathan: en fait ici c est la fonction de render
int			ft_raytracing_thread(t_setup *setup);
void		ft_setup_cam(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
size_t		ft_getobjscount(t_setup *setup);
t_bool		ft_plane_param(void *a, t_ray ray, double *dist);
t_bool		ft_sphere_param2(void *a, t_ray ray, double *dist);
t_bool		ft_sphere_param(t_ray *ray, void *a, double *t);

int			ft_mouse_hook(int mousecode, int x, int y, t_setup *setup);
int			ft_mouse_moove(int x, int y, t_setup *setup);
int			ft_expose_hook(t_setup *setup);
void		ft_print(t_setup *setup);
void		ft_start(t_setup *setup);
void		ft_path_maker(t_setup *setup);
int			ft_configure_dim(t_setup *setup);
size_t		ft_name_input(t_setup *setup);
size_t		ft_generate_map(t_setup *setup);
void		ft_path_maker_dir(t_setup *setup);
void		ft_mlx_control(t_setup *setup);
void		ft_mlx_control_key(t_setup *setup);
int			ft_sky_select(t_setup *setup);
int			ft_quit(t_setup *setup);
int			ft_select_color(t_setup *setup);
int			ft_give_color(t_setup *setup, t_color *color, int alpha);
void		ft_draw_vert_line(t_setup *setup, int posx, int len);

#endif
