/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:40:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 18:43:34 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			normal_sphere(t_ray ray, t_list *sph)
{
	return (ft_vec3normalize_r(ft_vec3vop_r(ft_vec3vop_r(ray.org, \
						ft_vec3sop_r(ray.dir, ray.dist, '*'), '+'), SPHERE(sph).ctr, '-')));
}

double			hit_sphere(t_ray ray, t_shape *form)
{
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		delta;

	oc = ft_vec3vop_r(ray.org, form->sph.ctr, '-');
	a = ft_vec3dot(ray.dir, ray.dir);
	b = 2.0 * ft_vec3dot(ray.dir, oc);
	c = ft_vec3dot(oc, oc) - (form->sph.r * form->sph.r);
	delta = b * b - 4.0 * a * c;
	if (delta <= 0.0)
		return (-1.0);
	if ((c = (-b - sqrt(delta)) / (2.0 * a)) > 0)
		return (c);
	else
		return ((-b + sqrt(delta)) / (2.0 * a));
}

t_col			intersec_sphere(t_ray ray, t_list *sph, t_scene *scene)
{
	t_vec3		norm;

	if (ray.dist >= 0.0)
	{
		norm = normal_sphere(ray, sph);
		return (diffuse(norm, sph, ray, FORM(sph)->mat));
	}
	return (scene->background);
}
