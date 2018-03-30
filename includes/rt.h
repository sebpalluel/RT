/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:45:17 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 18:49:54 by mbeilles         ###   ########.fr       */
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

# include <SDL.h>
# include "kernal.h"
# include "rtv1_struct.h"
# include "display_manager.h"
# include "keys.h"

# include "rtv1_define.h"
# include "libft.h"

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

# define C_NICK			C_ORANGE

/*
** =============================================================================
** 							Debug messages
** =============================================================================
*/

# define HEADER			C_MGREY "[" C_GREEN C_NICK C_MGREY "] "
# define HD				HEADER

# define ERR_HEADER(c)	HD " [" C_ERR "x" C_MGREY "] [" C_CODE c C_MGREY "] "
# define WRN_HEADER(sv)	HD " [" C_WRN "!" C_MGREY "] [" sv C_MGREY "] "
# define INF_HEADER		HD " [" C_INF "i" C_MGREY "] "

# define WRN_SEV_MINOR	C_YELLOW "Minor" C_NRM
# define WRN_SEV_MEDIUM	C_ORANGE "Unsafe" C_NRM
# define WRN_SEV_MAJOR	C_RED "Critical" C_NRM

# define STR_ERR(c, s)	ERR_HEADER(c) C_LGREY s "\n" C_NRM
# define STR_WRN(s, sv)	WRN_HEADER(sv) C_LGREY s "\n" C_NRM
# define STR_INF(s)		INF_HEADER C_LGREY s C_NRM "\n"

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
** 							Function typedefs
** =============================================================================
*/

typedef t_col	(*t_func_col)();
typedef double	(*t_func_dble)();
typedef char	*(*t_name_obj)();
typedef size_t	(*t_parse_obj)();
typedef	t_vec3	(*t_func_vec3)();
typedef t_vec3	(*t_func_uv_map)();
typedef	double	(*t_effects)();
typedef	SDL_Surface	*(*t_postproc)();

/*
** =============================================================================
** 							Function prototypes
** =============================================================================
*/

int			usage(int mode);
int			ft_quit(t_scene *scene);
void		ft_start(t_scene *scene);
char		**ft_validobjs(void); // ce qui contient tous les types d'objet qu'on gere pour le parsing
//t_objsparam	*ft_objsparam(void);
t_list		*ft_searchenv(t_list *env, char *name);
t_list		*ft_envlist(char *file);
t_list		*ft_newshape(void);
char		**ft_getenv(t_scene *scene);
t_list		*ft_newenv(char *name, char *value);
void		ft_editenv(t_list *env, char *name, char *value);
size_t		ft_args_to_fd(t_scene *scene);
char		*ft_getobjstr(char *str, char *obj);
char		*ft_getobjstrn(char **str, char *obj);
t_list		*ft_parse_scn(t_scene *scene, char *file);
void		ft_getengine(t_list **env, char *eng_str);
void		ft_getcams(t_list **env, char *cam_str);
void		ft_cam_change(t_scene *scene);
void		init_cam(t_cam *cam);
void		ft_getobjects(t_list **env, char *obj_str);
void		ft_getlights(t_scene *scene, t_list **env, char *light_str);
int			ft_setup_menu(t_scene *scene);
void		ft_setup_free(t_scene *scene);
size_t		ft_open_scene(t_scene *scene);
void		ft_sinvalintime(double *val, double min, double max, double speed);
void		ft_cosvalintime(double *val, double min, double max, double speed);

t_bool		ft_getvectfromenv(t_vec3 *vect, char *value);
t_bool		ft_getcolfromenv(t_col *col, char *value);
t_bool		ft_getdoublefromenv(double *val, char *value);
t_bool		ft_getsize_tfromenv(size_t *val, char *value);
t_bool		ft_checkifallset(t_bool *flag, size_t numvar);
void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name, \
		t_bool *no_val);
void		ft_getmaterial(t_list **env, char *mat_str);
void		ft_getspheres(t_list **env, char *obj_str);
void		ft_getplanes(t_list **env, char *obj_str);
void		ft_getcones(t_list **env, char *obj_str);
void		ft_getcylindres(t_list **env, char *obj_str);
void		ft_gettorus(t_list **env, char *obj_str);
void		ft_getmoebius(t_list **env, char *obj_str);
t_bool		*ft_mat_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag);
size_t		ft_getnumvar(size_t num_var_shape, t_list *form);

size_t		ft_engine(t_list **list);
size_t		ft_cam(t_list **list);
size_t		ft_light(t_list **list);
size_t		ft_plane(t_list **list);
size_t		ft_sphere(t_list **list);
size_t		ft_cone(t_list **list);
size_t		ft_cylindre(t_list **list);
size_t		ft_torus(t_list **list);
size_t		ft_moebius(t_list **list);

t_parse_obj	*parse_obj(void);
void		*ft_raytracing(void *a); // Nathan: en fait ici c est la fonction de render
int			ft_raytracing_thread(t_scene *scene);
size_t		ft_get_thread_n(t_scene *scene);
void		ft_setup_cam(t_scene *scene);
void		ft_put_pixel(t_scene *scene, int x, int y, int color);

// TODO Eliott functions
int			coltoi(t_col col);
int			init_mat(t_matrix *mat, int i, int j);
void		add_mat(t_matrix *a, t_matrix *b);
t_matrix	*mult_mat(t_matrix a, t_matrix b);
void		scale_mat(double a, t_matrix *res);
t_matrix	rot_mat(t_vec3 v, double theta);
t_matrix	id_mat(void);
t_vec3		mult_vec3_mat(t_matrix a, t_vec3 b);
t_vec3		rot_vec3(t_vec3 v, double theta, t_vec3 axis);

t_col		send_ray(t_ray ray, t_scene *scene);

t_func_col	*intersection(void);
t_func_dble	*hit_shape(void);
t_func_vec3	*normal_shape(void);

t_col		diffuse(t_vec3 norm, t_list *form, t_ray ray, t_mat mat_obj);
t_col		shadow(t_lgt *lgt, t_list *objects, t_vec3 hitpoint);
t_col		global_illum(t_ray ray, t_vec3 norm, t_vec3 origin, t_list *obj);
t_col		amb_light(t_col col, t_vec3 norm, t_vec3 dir, double amb_light);
t_ray		reflexion(t_ray ray, t_vec3 norm);
t_ray		refraction(t_ray ray, t_vec3 norm, double n2);

double		hit_plan(t_ray ray, t_shape *form);
double		hit_sphere(t_ray ray, t_shape *form);
double		hit_cone(t_ray ray, t_shape *form);
double		hit_cyl(t_ray ray, t_shape *form);
double		hit_tor(t_ray ray, t_shape *form);
double		hit_moe(t_ray ray, t_shape *form);
double		hit_obj(t_lgt *lgt, t_ray camray, t_list *form, t_list *obj);

t_col		intersec_sphere(t_ray ray, t_list *sph, t_scene *scene);
t_col		intersec_plan(t_ray ray, t_list *pln, t_scene *scene);
t_col		intersec_cone(t_ray ray, t_list *con, t_scene *scene);
t_col		intersec_cyl(t_ray ray, t_list *cyl, t_scene *scene);
t_col		intersec_tor(t_ray ray, t_list *tor, t_scene *scene);
t_col		intersec_moe(t_ray ray, t_list *moe, t_scene *scene);

t_vec3		normal_plane(t_ray ray, t_list *plane);
t_vec3		normal_cyl(t_ray ray, t_list *cyl);
t_vec3		normal_cone(t_ray ray, t_list *cone);
t_vec3		normal_sphere(t_ray ray, t_list *sph);
t_vec3		normal_tor(t_ray ray, t_list *tor);
t_vec3		normal_moe(t_ray ray, t_list *moe);

t_ray		init_ray(t_vec3 org, t_vec3 dir);

t_vec3		rand_directed_vec(t_vec3 dir);
t_effects	*effects(void);
void		perlin_draw_test(t_scene *scene, t_pix pix);
float		ft_perlin_noise(double x, double y, double z);
double		ft_perlin(t_vec3 vec3, t_gen gen);
double		ft_marble(t_vec3 vec3, t_gen gen);
double		ft_zebra(t_vec3 vec3, t_gen gen);
double		ft_wood(t_vec3 vec3, t_gen gen);
double		ft_cloud(t_vec3 vec3, t_gen gen);
double		ft_checker(t_vec3 vec3, t_gen gen);

SDL_Surface	*ft_sepia(SDL_Surface *s);
SDL_Surface	*ft_blur(SDL_Surface *s);
SDL_Surface	*ft_cel_shading(SDL_Surface *s);
SDL_Surface	*ft_blackandwhite(SDL_Surface *s);
SDL_Surface	*ft_negative(SDL_Surface *s);
SDL_Surface	*ft_effect_change(SDL_Surface *s);
t_postproc	*postprocess(void);

// Nathan
t_text **get_texture(void);
t_text *get_texture_datas(char *path);
t_mat get_mat_at(t_vec3 hit, t_list *form, t_mat mat_obj);
void fit_and_scale(double *u, double *v, t_text *text, t_text_c tex_c);
t_vec3 get_x_axe(t_vec3 dir);
void get_local_coords(t_vec3 hit, t_vec3 *coord, t_vec3 orig, t_vec3 dir);
t_func_uv_map	*uv_map(void);
t_vec3		uv_map_sph(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);
t_vec3		uv_map_pln(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);
t_vec3		uv_map_cyl(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);
t_vec3		uv_map_cone(t_vec3 hit, t_list *form, t_mat *mat, t_text *text);

double	ft_2min_pos(double a, double b);
double	ft_resolve_cubic_min(double a, double b, double c, double d);
double	ft_resolve_quadric_min(double b, double c, double d, double e);

//Maxime
void					leave(char *msg, uint32_t exit_code);



/*
** =============================================================================
** 							Globales
** =============================================================================
*/

static const unsigned char	g_perm[512] = {
	217, 150, 31, 204, 241, 104, 201, 34, 39, 210, 177, 232, 160, 162, 128, \
	102, 2, 26, 95, 134, 108, 194, 143, 230, 216, 228, 82, 212, 168, 118, 67, \
	48, 213, 236, 158, 142, 225, 2, 133, 156, 29, 72, 231, 41, 235, 15, \
	49, 178, 12, 5, 27, 180, 195, 44, 60, 9, 138, 130, 197, 198, 21, \
	8, 152, 252, 114, 172, 46, 54, 101, 220, 8, 90, 48, 65, 206, 1, \
	18, 59, 191, 240, 139, 30, 205, 77, 233, 33, 32, 6, 215, 38, 10, \
	5, 199, 53, 73, 28, 196, 51, 221, 246, 69, 58, 187, 200, 87, 242, \
	6, 202, 94, 136, 253, 234, 237, 226, 3, 250, 92, 11, 219, 85, 22, \
	13, 151, 24, 159, 88, 243, 125, 207, 61, 126, 13, 227, 80, 175, 70, \
	0, 132, 20, 64, 186, 224, 17, 244, 120, 68, 7, 75, 81, 89, 181, \
	6, 161, 91, 40, 49, 211, 155, 249, 164, 79, 166, 179, 248, 131, 214, \
	05, 57, 222, 122, 174, 135, 176, 115, 74, 19, 25, 173, 251, 154, 93, \
	54, 203, 63, 43, 71, 18, 106, 55, 190, 141, 165, 245, 119, 123, 103, \
	3, 47, 37, 184, 76, 52, 185, 112, 107, 145, 84, 116, 147, 183, 209, \
	00, 223, 121, 189, 169, 208, 45, 14, 36, 0, 146, 127, 97, 66, 157, \
	47, 193, 144, 167, 238, 171, 239, 4, 96, 99, 137, 117, 170, 182, 109, \
	11, 140, 78, 229, 124, 129, 188, 42, 153, 23, 110, 192, 163, 16, 217, \
	50, 31, 204, 241, 104, 201, 34, 39, 210, 177, 232, 160, 162, 128, 102, \
	2, 26, 95, 134, 108, 194, 143, 230, 216, 228, 82, 212, 168, 118, 67, \
	48, 213, 236, 158, 142, 225, 2, 133, 156, 29, 72, 231, 41, 235, 15, \
	49, 178, 12, 5, 27, 180, 195, 44, 60, 9, 138, 130, 197, 198, 21, \
	8, 152, 252, 114, 172, 46, 54, 101, 220, 8, 90, 48, 65, 206, 1, \
	18, 59, 191, 240, 139, 30, 205, 77, 233, 33, 32, 6, 215, 38, 10, \
	5, 199, 53, 73, 28, 196, 51, 221, 246, 69, 58, 187, 200, 87, 242, \
	6, 202, 94, 136, 253, 234, 237, 226, 3, 250, 92, 11, 219, 85, 22, \
	13, 151, 24, 159, 88, 243, 125, 207, 61, 126, 13, 227, 80, 175, 70, \
	0, 132, 20, 64, 186, 224, 17, 244, 120, 68, 7, 75, 81, 89, 181, \
	6, 161, 91, 40, 49, 211, 155, 249, 164, 79, 166, 179, 248, 131, 214, \
	05, 57, 222, 122, 174, 135, 176, 115, 74, 19, 25, 173, 251, 154, 93, \
	54, 203, 63, 43, 71, 18, 106, 55, 190, 141, 165, 245, 119, 123, 103, \
	3, 47, 37, 184, 76, 52, 185, 112, 107, 145, 84, 116, 147, 183, 209, \
	00, 223, 121, 189, 169, 208, 45, 14, 36, 0, 146, 127, 97, 66, 157, \
	47, 193, 144, 167, 238, 171, 239, 4, 96, 99, 137, 117, 170, 182, 109};

static const t_vec3			g_gradtab[16] = {
	{ 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 }, \
	{ 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 }, \
	{ 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 }, \
	{ 1, 1, 0 }, { -1, 1, 0 }, { 0, -1, 1 }, { 0, -1, -1 }
};

static const t_vec3			g_unitcube[8] = {
	{ 0, 0, 0 }, { -1, 0, 0 }, { 0, -1, 0 }, { -1, -1, 0 }, \
	{ 0, 0, -1 }, { 0, -1, -1 }, { 0, -1, -1 }, { -1, -1, -1 }
};

static size_t	g_time = 0;

#endif
