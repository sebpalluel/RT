/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:25:18 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/04 21:16:08 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../includes/rtv1_define.h"
# include "../includes/rtv1_struct.h"
# include "../includes/rtv1_global.h"
# include <time.h>
# include <sys/time.h>
# include <SDL_image.h>
# include <SDL.h>

int				usage(t_error mode);
int				ft_quit(t_setup *setup);
void			ft_start(t_setup *setup);
void			ft_mlx_control_key(t_setup *setup);
void			ft_mlx_control(t_setup *setup);
void			ft_cam_select(t_setup *setup);
void			ft_effect_select(t_setup *setup);
void			ft_take_screenshot(t_setup *setup);
t_setup			*ft_setup_alloc(t_setup *setup);
char			**ft_validobjs(void);
t_list			*ft_searchenv(t_list *env, char *name);
t_list			*ft_envlist(char *file);
t_list			*ft_newshape(void);
char			**ft_getenv(t_setup *setup);
t_list			*ft_newenv(char *name, char *value);
void			ft_editenv(t_list *env, char *name, char *value);
size_t			ft_args_to_fd(t_setup *setup);
char			*ft_getobjstr(char *str, char *obj);
char			*ft_getobjstrn(char **str, char *obj);
t_list			*ft_parse_scn(t_setup *setup, char *file);
void			ft_getengine(t_list **env, char *eng_str);
void			ft_getcams(t_list **env, char *cam_str);
void			ft_cam_change(t_setup *setup);
void			init_cam(t_cam *cam);
void			ft_getobjects(t_list **env, char *obj_str);
void			ft_getlights(t_setup *setup, t_list **env, char *light_str);
int				ft_setup_menu(t_setup *setup);
void			ft_setup_free(t_setup *setup);
size_t			ft_select_scene(t_setup *setup, int scene);
size_t			ft_open_scene(t_setup *setup);
void			ft_put_pixel(t_setup *setup, int x, int y, int color);
void			ft_mlx_process(t_setup *setup);
int				ft_expose(t_setup *setup);
void			ft_put_pxl_to_img(t_setup *setup, t_vec3 pos, t_color *clr);
void			ft_sinvalintime(double *val, double min, double max,
		double speed);
void			ft_cosvalintime(double *val, double min, double max,
		double speed);
void			ft_saveimg(t_scene scn, char *name);
char			*ft_savename(const char *name, size_t counter);
int				ft_loop_hook(t_setup *setup);
int				ft_key_hook(int keycode, t_setup *setup);

t_bool			ft_getvectfromenv(t_vec3 *vect, char *value);
t_bool			ft_getcolfromenv(t_col *col, char *value);
t_bool			ft_getdoublefromenv(double *val, char *value);
t_bool			ft_getsize_tfromenv(size_t *val, char *value);
t_bool			ft_checkifallset(t_bool *flag, size_t numvar);
void			ft_getvaluetoenv(t_list **env, char *obj_str, const char *name,
		t_bool *no_val);
void			ft_getmaterial(t_list **env, char *mat_str);
void			ft_getspheres(t_list **env, char *obj_str);
void			ft_getplanes(t_list **env, char *obj_str);
void			ft_getcones(t_list **env, char *obj_str);
void			ft_getcylindres(t_list **env, char *obj_str);
void			ft_gettorus(t_list **env, char *obj_str);
void			ft_getmoebius(t_list **env, char *obj_str);
t_bool			*ft_mat_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag);
size_t			ft_getnumvar(size_t num_var_shape, t_list *form);

size_t			ft_engine(t_list **list);
size_t			ft_cam(t_list **list);
size_t			ft_light(t_list **list);
size_t			ft_plane(t_list **list);
size_t			ft_sphere(t_list **list);
size_t			ft_cone(t_list **list);
size_t			ft_cylindre(t_list **list);
size_t			ft_torus(t_list **list);
size_t			ft_moebius(t_list **list);

t_parse_obj		*parse_obj(void);
void			*ft_raytracing(void *a);
int				ft_raytracing_thread(t_setup *setup);
size_t			ft_get_thread_n(t_setup *setup);
void			ft_setup_cam(t_setup *setup);
void			ft_put_pixel(t_setup *setup, int x, int y, int color);

t_setup			*get_st(void);
int				coltoi(t_col col);
t_col			ft_get_pixel_col(t_setup *setup, int x, int y);
int				init_mat(t_matrix *mat, int i, int j);
void			add_mat(t_matrix *a, t_matrix *b);
t_matrix		*mult_mat(t_matrix a, t_matrix b);
void			scale_mat(double a, t_matrix *res);
t_matrix		rot_mat(t_vec3 v, double theta);
t_matrix		id_mat(void);
t_vec3			mult_vec3_mat(t_matrix a, t_vec3 b);
t_vec3			rot_vec3(t_vec3 v, double theta, t_vec3 axis);

t_col			send_ray(t_ray ray, t_setup *setup);

t_func_col		*intersection(void);
t_func_dble		*hit_shape(void);
t_func_vec3		*normal_shape(void);

t_col			diffuse(t_vec3 norm, t_list *form, t_ray ray, t_mat mat_obj);
void			shadow(t_lgt lgt, t_list *objects, t_vec3 hitpoint,
		t_col *shad);
t_col			global_illum(t_ray ray, t_vec3 norm, t_vec3 origin);
t_col			amb_light(t_col col, t_vec3 norm, t_vec3 dir, double amb_light);
t_ray			reflexion(t_ray ray, t_vec3 norm);
t_ray			refraction(t_ray ray, t_vec3 norm, double n2);

double			hit_plan(t_ray ray, t_shape *form);
double			hit_sphere(t_ray ray, t_shape *form);
double			hit_cone(t_ray ray, t_shape *form);
double			hit_cyl(t_ray ray, t_shape *form);
double			hit_tor(t_ray ray, t_shape *form);
double			hit_moe(t_ray ray, t_shape *form);
double			hit_obj(t_lgt *lgt, t_ray camray, t_list *form, t_list *obj);

t_col			intersec_sphere(t_ray ray, t_list *sph, t_setup *setup);
t_col			intersec_plan(t_ray ray, t_list *pln, t_setup *setup);
t_col			intersec_cone(t_ray ray, t_list *con, t_setup *setup);
t_col			intersec_cyl(t_ray ray, t_list *cyl, t_setup *setup);
t_col			intersec_tor(t_ray ray, t_list *tor, t_setup *setup);
t_col			intersec_moe(t_ray ray, t_list *moe, t_setup *setup);

t_vec3			normal_plane(t_ray ray, t_list *plane);
t_vec3			normal_cyl(t_ray ray, t_list *cyl);
t_vec3			normal_cone(t_ray ray, t_list *cone);
t_vec3			normal_sphere(t_ray ray, t_list *sph);
t_vec3			normal_tor(t_ray ray, t_list *tor);
t_vec3			normal_moe(t_ray ray, t_list *moe);

t_ray			init_ray(t_vec3 org, t_vec3 dir);

t_vec3			rand_directed_vec(t_vec3 dir);
t_effects		*effects(void);
void			perlin_draw_test(t_setup *setup, t_pix pix);
float			ft_perlin_noise(double x, double y, double z);
double			ft_perlin(t_vec3 vec3, t_gen gen);
double			ft_marble(t_vec3 vec3, t_gen gen);
double			ft_zebra(t_vec3 vec3, t_gen gen);
double			ft_wood(t_vec3 vec3, t_gen gen);
double			ft_cloud(t_vec3 vec3, t_gen gen);
double			ft_checker(t_vec3 vec3, t_gen gen);

t_col			ft_sepia(t_setup *setup, int x, int y);
t_col			ft_blur(t_setup *setup, int x, int y);
t_col			ft_cel_shading(t_setup *setup, int x, int y);
t_col			ft_blackandwhite(t_setup *setup, int x, int y);
t_col			ft_negative(t_setup *setup, int x, int y);
void			ft_effect_change(t_setup *setup, int effect);
t_postproc		*postprocess(void);

t_text			**get_texture(void);
t_text			*get_texture_datas(char *path);
t_mat			get_mat_at(t_vec3 hit, t_list *form, t_mat mat_obj);
void			fit_and_scale(double *u, double *v, t_text *text,
		t_text_c tex_c);
t_vec3			get_x_axe(t_vec3 dir);
void			get_local_coords(t_vec3 hit, t_vec3 *coord, t_vec3 orig,
		t_vec3 dir);
t_func_uv_map	*uv_map(void);
t_vec3			uv_map_sph(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);
t_vec3			uv_map_pln(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);
t_vec3			uv_map_cyl(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);
t_vec3			uv_map_cone(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);

double			ft_2min_pos(double a, double b);
double			ft_cubic_derivative_estimate(double a, double b, \
												double c, double x);
int				ft_resolve_cubic_min(double *a, double *b, double *c, double d);
double			ft_cubic_estimate(double a, double b, double c, double x);
double			ft_resolve_quadric_min(double b, double c, double d, double e);
void			ft_sort_pos(double *a, double *b, double *c);
t_vec3			change_base(t_vec3 a, t_vec3 x, t_vec3 y);
double			moeb_calc1(t_vec3 d);
double			moeb_calc2(t_vec3 d, t_vec3 o, double r);
double			moeb_calc3(t_vec3 d, t_vec3 o, double r);
double			moeb_calc4(t_vec3 o, double r);
double			det_mat(t_vec3 a, t_vec3 b, t_vec3 c);
double			lambert(t_ray ray, t_vec3 norm, t_lgt lgt);
double			phong(t_ray ray, t_mat mat, t_vec3 norm, t_lgt light);

char			*get_default_scenes_path(int scene);
#endif
