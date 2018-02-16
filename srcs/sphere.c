/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:40:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 13:11:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_sphere_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "position") == 0)
		flag[0] = ft_getvec3fromenv(&SPHERE[NSPHERE].pos, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[1] = ft_getdoublefromenv(&SPHERE[NSPHERE].rad, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&SPHERE[NSPHERE].mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[3] = ft_getdoublefromenv(&SPHERE[NSPHERE].mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[4] = ft_getdoublefromenv(&SPHERE[NSPHERE].mat.specular, \
				ENVSTRUCT(env)->value);
	SPHERE[NSPHERE].num_arg++;
}


size_t			ft_sphere(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARSPHERE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARSPHERE);
	while (SPHERE[NSPHERE].num_arg < NVARSPHERE && env && (env = env->next))
		ft_sphere_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARSPHERE) != OK)
		return (SETUP.error = SPHERE_ERROR);
	NSPHERE++;
	*list = env;
	return (OK);
}

static double	ft_spherefromdisk(double abc[3], double distSqrt)
{
	double		t[2];
	double		q;
	double		swap;

	q = (abc[1] < 0. ? (-abc[1] - distSqrt) / 2. : (-abc[1] + distSqrt) / 2.);
	t[0] = q / abc[0];
	t[1] = abc[2] / q;
	if (t[0] > t[1])
	{
		swap = t[0];
		t[0] = t[1];
		t[1] = swap;
	}
	if (t[1] < 0.)
		return (0.);
	else if (t[0] < 0.)
		return (t[1]);
	else
		return (t[0]);
}
/* TODO
**	fonction d intersections
**	bool intersect(const Ray &ray) const
**		{
**		        float t0, t1; // solutions for t if the ray intersects
**		#if 0
**		        // geometric solution
**		        Vec3f L = center - orig;
**		        float tca = L.dotProduct(dir);
**		        // if (tca < 0) return false;
**		        float d2 = L.dotProduct(L) - tca * tca;
**		        if (d2 > radius2) return false;
**		        float thc = sqrt(radius2 - d2);
**		        t0 = tca - thc;
**		        t1 = tca + thc;
**		#else  ON GARDE CELLE LA
**		        // analytic solution
**		        Vec3f L = orig - center;
**		        float a = dir.dotProduct(dir);
**		        float b = 2 * dir.dotProduct(L);
**		        float c = L.dotProduct(L) - radius2;
**		        if (!solveQuadratic(a, b, c, t0, t1)) return false;
**		#endif
**		        if (t0 > t1) std::swap(t0, t1);
**
**		        if (t0 < 0) {
**		            t0 = t1; // if t0 is negative, let's use t1 instead
**		            if (t0 < 0) return false; // both t0 and t1 are negative
**		        }
**
**		        t = t0;
**
**		        return true;
**		}
**
**	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
**	{
**	    float discr = b * b - 4 * a * c;
**	    if (discr < 0) return false;
**	    else if (discr == 0) x0 = x1 = - 0.5 * b / a;
**	    else {
**	        float q = (b > 0) ?
**	            -0.5 * (b + sqrt(discr)) :
**	            -0.5 * (b - sqrt(discr));
**	        x0 = q / a;
**	        x1 = c / q;
**	    }
**	    if (x0 > x1) std::swap(x0, x1);
**
**	    return true;
**	}
*/

t_bool solve_quadratic(double *abc, float *t0, float *t1) {
	float discr;
	float q;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];

	if (discr < 0)
	{
		return FALSE;
	}
	else if ( discr == 0) {
		*t0 =  -.05 * abc[1] / abc[0];
	} else {
		q = (abc[1] > 0) ? -0.5 * (abc[1] + sqrt(discr)) : -0.5 * (abc[1] - sqrt(discr));
		*t0 = q / abc[0];
		*t1 = abc[2] / q;
	}
	if (t0 > t1)
		ft_swap(t0, t1, sizeof(float));
	return (TRUE);
}

t_bool		ft_sphere_param(t_ray *ray, void *a, double *t) {
	t_setup		*setup;
	float t0;
	float t1;
	t_vec3 L;
	setup = (t_setup *)a;
	double		abc[3] = {0, 0, 0};

	L = ft_vec3vop_r(ray->orig, SPHERE[SPH_N].pos, '-');
	abc[0] = ft_dotproduct(ray->dir, ray->dir);
	abc[1] = 2. * ft_dotproduct(ray->dir, L);
	abc[2] = ft_dotproduct(L, L) - SQUARE(SPHERE[SPH_N].rad);
	if (!solve_quadratic(abc, &t0, &t1))
	{
		return FALSE;
	}
	if (t0 > t1)
	{
		ft_swap(&t0, &t1, sizeof(float));
	}
	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0)
		{
			return FALSE;
		}
	}
	*t = t0;
	return (TRUE);

	/*
	float t0, t1; // solutions for t if the ray intersects
	Vec3f L = orig - center;
	**		        float a = dir.dotProduct(dir);
	**		        float b = 2 * dir.dotProduct(L);
	**		        float c = L.dotProduct(L) - radius2;
	**		        if (!solveQuadratic(a, b, c, t0, t1)) return false;
	if (t0 > t1) std::swap(t0, t1);
	**
	**		        if (t0 < 0) {
	**		            t0 = t1; // if t0 is negative, let's use t1 instead
	**		            if (t0 < 0) return false; // both t0 and t1 are negative
	**		        }
	**
	**		        t = t0;
	**
	**		        return true;
	*/
}

t_bool		ft_sphere_param2(void *a, t_ray ray, double *dist)
{
	t_setup		*setup;
	t_vec3		ro_sc;
	double		abc[3] = {0, 0, 0};
	double		disk;

	setup = (t_setup *)a;
	*dist = 0;
	abc[0] = ft_dotproduct(ray.dir, ray.dir);
	ft_vec3vop(&ro_sc, ray.orig, SPHERE[SPH_N].pos, '-');
	abc[1] = 2. * ft_dotproduct(ray.dir, ro_sc);
	abc[2] = ft_dotproduct(ro_sc, ro_sc) - SQUARE(SPHERE[SPH_N].rad);
	SPH_N++; //ici doit bien incrementer l'index pour passer aux objets suivants
	if (((disk = SQUARE(abc[1]) - 4 * abc[0] * abc[2]) < 0) || \
			(*dist = ft_spherefromdisk(abc, sqrt(disk))) == 0.)
		return (ERROR); // pas hit
	return (OK); // ici on part du principe qu'il a hit
}
