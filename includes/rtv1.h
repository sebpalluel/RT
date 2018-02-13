/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:25:18 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/09 17:12:18 by psebasti         ###   ########.fr       */
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
t_list		*ft_envlist(char **envp);
char		**ft_getenv(t_setup *setup);
void		ft_editenv(t_list *env, char *name, char *value);
size_t		ft_args_to_fd(t_setup *setup);
size_t		ft_setup_mode(t_setup *setup, size_t mode);
int			ft_setup_menu(t_setup *setup);
size_t		ft_select_map(t_setup *setup);
int			ft_save_map(t_setup *setup);
void		ft_draw_map(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
void		ft_mlx_process(t_setup *setup);
void		ft_put_pxl_to_img(t_setup *setup, t_vec3 pos, t_color *clr);
t_bool		ft_getvec3fromenv(t_vec3 *vec3, char *value);
t_bool		ft_getcolfromenv(t_color *col, char *value);
t_bool		ft_getfloatfromenv(float *val, char *value);
t_bool		ft_checkifallset(t_bool *flag, size_t numvar);
size_t		ft_cam(void *a, t_list **list);
size_t		ft_light(void *a, t_list **list);
size_t		ft_plane(void *a, t_list **list);
size_t		ft_sphere(void *a, t_list **list);
int			ft_raytracing(t_setup *setup);
void		ft_setup_cam(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
size_t		ft_getobjscount(t_setup *setup);
t_bool		ft_plane_param(void *a, t_ray ray, double *dist);
t_bool		ft_sphere_param2(void *a, t_ray ray, double *dist);
t_bool		ft_sphere_param(t_ray *ray, void *a);

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
size_t		ft_open_map(t_setup *setup);
void		ft_pos_player(t_setup *setup);
size_t		ft_ray_casting(t_setup *setup);
void		ft_mlx_control(t_setup *setup);
void		ft_mlx_control_key(t_setup *setup);
int			ft_sky_select(t_setup *setup);
int			ft_quit(t_setup *setup);
int			ft_select_color(t_setup *setup);
int			ft_give_color(t_setup *setup, t_color *color, int alpha);
void		ft_draw_vert_line(t_setup *setup, int posx, int len);

#endif
