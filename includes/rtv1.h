/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:25:18 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 11:42:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../includes/rtv1_struct.h"
# include "../includes/rtv1_define.h"

int			usage(int mode);
int			ft_quit(t_setup *setup);
void		ft_setup_free(t_setup *setup);
void		ft_start(t_setup *setup);
void		ft_mlx_control_key(t_setup *setup);
t_setup		*ft_setup_alloc(t_setup *setup);
char		**ft_validobjs(void);
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
t_bool		ft_getvectfromenv(t_vec3 *vect, char *value);
t_bool		ft_getcolfromenv(t_col *col, char *value);
t_bool		ft_getdoublefromenv(double *val, char *value);
t_bool		ft_getsize_tfromenv(size_t *val, char *value);
t_bool		ft_checkifallset(t_bool *flag, size_t numvar);
size_t		ft_engine(t_list **list);
size_t		ft_cam(t_list **list);
size_t		ft_light(t_list **list);
size_t		ft_plane(t_list **list);
size_t		ft_sphere(t_list **list);
size_t		ft_cone(t_list **list);
t_parse_obj	*parse_obj(void);
void		*ft_raytracing(void *cam);
int			ft_raytracing_thread(t_setup *setup);
size_t		ft_get_thread_n(t_setup *setup);
void		ft_setup_cam(t_setup *setup);
void		ft_put_pixel(t_setup *setup, int x, int y, int color);
t_bool		ft_plane_param(t_ray *ray, t_forms *form, double *t);
t_bool		ft_sphere_param(t_ray *ray, t_forms *form, double *t);
t_setup		*get_st(void);
t_param		*param(void);
t_bool		solve_quadratic(double *abc, float *t0, float *t1);
t_bool		ft_solve_quadra(double abc[3], double *t);
t_bool		ft_cone_intersect(t_ray *ray, t_forms *form, double *t);
void		ft_cldre_struct_pop(t_list *form, t_list *env, t_bool *flag);
size_t		ft_cldre(t_list **list);
void		ft_getcylindres(t_list **env, char *obj_str);
t_bool		ft_cldre_intersect(t_ray *ray, t_forms *form, double *t);
t_func_nrml	*get_nrml(void);
t_col		mult_scale_col_limited(double t, t_col col);
void		mult_dir_matrix(t_vec3 *src, t_vec3 *dst, double **x);
void		mult_vec3_matrix(t_vec3 src, t_vec3 *dst, double **x);
void		illuminate(t_hit *hit, t_mat mat, t_lgt *light);
void		init_sdw_ray(t_ray *sdw_ray, t_lgt *light, t_hit *hit);
void		ft_look_at(t_setup *setup, t_cam *cam);
void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name);
void		ft_getmaterial(t_list **env, char *mat_str);
void		ft_getspheres(t_list **env, char *obj_str);
void		ft_getplanes(t_list **env, char *obj_str);
void		ft_getcones(t_list **env, char *obj_str);
void		ft_getcylindres(t_list **env, char *obj_str);

#endif
