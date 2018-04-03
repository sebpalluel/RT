/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 20:53:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3			normal_plane(t_ray ray, t_list *plane)
{
	t_vec3		norm;

	norm = PLAN(plane).nrml;
	if (ft_vec3dot(PLAN(plane).nrml, ray.dir) > 0)
		norm = ft_vec3sop_r(PLAN(plane).nrml, -1, '*');
	return (norm);
}

double			hit_plan(t_ray ray, t_shape *form)
{
	double		a;
	double		b;

	a = ft_vec3dot(ray.dir, form->plan.nrml);
	if (a == 0)
		return (-1);
	b = ft_vec3dot(form->plan.nrml, ft_vec3vop_r(ray.org,
				ft_vec3sop_r(form->plan.nrml, form->plan.dst, '*'), '+'));
	return (-b / a);
}

t_col			intersec_plan(t_ray ray, t_list *pln, t_setup *setup)
{
	t_vec3		norm;

	if (ray.dist >= 0.0)
	{
		norm = normal_plane(ray, pln);
		return (diffuse(norm, pln, ray, FORM(pln)->mat));
	}
	return (setup->background);
}
