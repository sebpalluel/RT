/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:05:12 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 18:58:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** =============================================================================
** 							Includes
** =============================================================================
*/

# include "rt.h"

/*
** =============================================================================
** 							Defines
** =============================================================================
*/

# define ENG_S		parsed[0]
# define CAM_S		parsed[1]
# define LGT_S		parsed[2]
# define OBJ_S		parsed[3]

# define P_ENV(x)	((t_p_env *)(*(x)).content)

# define NUM_FORM		6
# define NUM_OBJS		9
# define NUM_EFFECTS	5
# define NUM_PROC		6
# define NUM_TEXT		2

# define MAX_WINDOW		5
# define MAX_CAM		10
# define MAX_SIZE		10000
# define MAX_OBJ		20

# define M_TEX			1
# define M_GEN			2
# define NVARTEX		3
# define NVARGEN		5
# define NVARMAT		5
# define NVARMAT_MAX	NVARMAT + NVARGEN
# define NVARENG		2
# define NVARCAM		2
# define NVARLIGHT		4
# define NVARSPHERE		2
# define NVARPLANE		2
# define NVARCONE		3
# define NVARCYLINDRE	3
# define NVARTORUS		4
# define NVARMOEBIUS	5

/*
** =============================================================================
** 							Typedefs
** =============================================================================
*/

typedef struct		s_p_env
{
	char			*name;
	char			*value;
}					t_p_env;

/*
** =============================================================================
** 							Function typedefs
** =============================================================================
*/

typedef char	*(*t_name_obj)();
typedef size_t	(*t_parse_obj)();

/*
** =============================================================================
** 							Prototypes
** =============================================================================
*/
t_list		*ft_new_p_env(char *name, char *value);
t_list		*ft_newshape(void);
char		*ft_getobjstr(char *str, char *obj);
char		*ft_getobjstrn(char **str, char *obj);

t_bool		*ft_mat_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag);
t_bool		ft_getvectfromenv(t_vec3 *vect, char *value);
t_bool		ft_getcolfromenv(t_col *col, char *value);
t_bool		ft_getdoublefromenv(double *val, char *value);
t_bool		ft_getsize_tfromenv(size_t *val, char *value);
t_bool		ft_checkifallset(t_bool *flag, size_t numvar);

void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name, \
		t_bool *no_val);
void		ft_getengine(t_scene *scn, t_list **env, char *eng_str);
void		ft_getcams(t_scene *scn, t_list **env, char *cam_str);
void		ft_getobjects(t_scene *scn, t_list **env, char *obj_str);
void		ft_getlights(t_scene *scene, t_list **env, char *light_str);
void		ft_getmaterial(t_scene *scn, t_list **env, char *mat_str);
void		ft_getspheres(t_scene *scn, t_list **env, char *obj_str);
void		ft_getplanes(t_scene *scn, t_list **env, char *obj_str);
void		ft_getcones(t_scene *scn, t_list **env, char *obj_str);
void		ft_getcylindres(t_scene *scn, t_list **env, char *obj_str);
void		ft_gettorus(t_scene *scn, t_list **env, char *obj_str);
void		ft_getmoebius(t_scene *scn, t_list **env, char *obj_str);
size_t		ft_getnumvar(size_t num_var_shape, t_list *form);

size_t		ft_engine(t_scene *scn, t_list **list);
size_t		ft_cam(t_scene *scn, t_list **list);
size_t		ft_light(t_scene *scn, t_list **list);
size_t		ft_plane(t_scene *scn, t_list **list);
size_t		ft_sphere(t_scene *scn, t_list **list);
size_t		ft_cone(t_scene *scn, t_list **list);
size_t		ft_cylindre(t_scene *scn, t_list **list);
size_t		ft_torus(t_scene *scn, t_list **list);
size_t		ft_moebius(t_scene *scn, t_list **list);

char		**ft_validobjs(void); // ce qui contient tous les types d'objet qu'on gere pour le parsing
t_parse_obj	*parse_obj(void);
t_scene		*ft_open_scene(const char *path);
t_list		*ft_parse_scn(t_scene *scn, char *file);


/*
** =============================================================================
*/

#endif
