/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 16:50:12 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_plane_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "position") == 0)
		flag[0] = ft_getvec3fromenv(&PLANE[NPLANE].pos, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "norm") == 0)
		flag[1] = ft_getvec3fromenv(&PLANE[NPLANE].norm, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[4] = ft_getcolfromenv(&PLANE[NPLANE].mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[5] = ft_getdoublefromenv(&PLANE[NPLANE].mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[6] = ft_getdoublefromenv(&PLANE[NPLANE].mat.specular, \
				ENVSTRUCT(env)->value);
	PLANE[NPLANE].num_arg++;
}


size_t			ft_plane(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARPLANE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARPLANE);
	while (PLANE[NPLANE].num_arg < NVARPLANE && env && (env = env->next))
		ft_plane_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARPLANE) != OK)
		return (SETUP.error = PLANE_ERROR);
	NPLANE++;
	*list = env;
	return (OK);
}

// t_bool		ft_plane_param( t_ray *ray, void *a, double *t)
// {
// 	t_setup		*setup;
//
// 	setup = (t_setup *)a;
// 	*dist = 0;
// 	ray.size = 0;
// 	PL_N++;
// 	return (OK);
// }

t_bool	ft_plane_param(t_ray *ray, void *a, double *t)
{
	t_setup	*setup;
	double		denom;
	t_vec3	diff;

	setup = (t_setup *)a;
	denom = ft_dotproduct(PLANE[PL_N].norm, ray->dir);
	if (denom > 0.000001)
	{
		diff = ft_vec3vop_r(PLANE[PL_N].pos, ray->orig, '-');
		*t = ft_dotproduct(diff, PLANE[PL_N].norm) / denom;
		return (t >= 0);
	}
	return (FALSE);
}

/*
**			typedef struct		s_plane
**			{
**				t_vec3			pos;
**				t_vec3			norm;
**				t_mat			mat;
**				size_t			num_arg;
**			}					t_plane;
**
**		bool intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, float &t)
**		{
**				A plane can be defined as a point (p0) representing how far the plane is from the world origin
**				 and a normal (defining the orientation of the plane) (n)
**
**		    // assuming vectors are all normalized
**				n = normale du plan permettant de ledef sa "direction"
**				l = direction du rayon
**				t = the parametric distance from the origin of the ray to the point of interest along the ray
**				1e-6 => valeur tres faible 0.000001
**		    float denom = dotProduct(n, l);
**		    if (denom > 1e-6) {
**		        Vec3f p0l0 = p0 - l0; (l0 -> origine du rayon)
**		        t = dotProduct(p0l0, n) / denom;
**		        return (t >= 0);
**		    }
**
**		    return false;
**		}
*/
