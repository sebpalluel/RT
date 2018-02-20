/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 11:38:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_plane_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "normale") == 0)
		flag[0] = ft_getvectfromenv(&PLAN(form).nrml, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "distance") == 0)
		flag[1] = ft_getdoublefromenv(&PLAN(form).dst, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&PLAN(form).mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[3] = ft_getdoublefromenv(&PLAN(form).mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[4] = ft_getdoublefromenv(&PLAN(form).mat.specular, \
				ENVSTRUCT(env)->value);
	FORM(form)->num_arg++;
}


size_t			ft_plane(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARPLANE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARPLANE);
	ft_lstaddend(&SCN.forms, ft_newform());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = PLN;
	while (FORM(form)->num_arg < NVARPLANE && env && (env = env->next))
		ft_plane_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARPLANE) != OK)
		return (setup->error = PLANE_ERROR);
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

t_bool	ft_plane_param(t_ray *ray, t_forms *form, double *t)
{
	double		denom;
	// t_vec3	diff;

	denom = ft_dotproduct(form->plan.nrml, ray->dir);
	if (denom > 0.000001)
	{
		*t = ft_dotproduct(form->plan.nrml, ft_vec3vop_r(ray->org,
					ft_vec3sop_r(form->plan.nrml, form->plan.dst, '*'), '-'));
		// diff = ft_vec3vop_r(PLANE[PL_N].pos, ray->orig, '-');
		// *t = ft_dotproduct(diff, PLANE[PL_N].norm) / denom;
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
