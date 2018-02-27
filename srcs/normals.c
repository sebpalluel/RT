/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 17:17:31 by nchalot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_vec3	normal_cone(t_ray ray, t_forms *form)
{
	double		height;
	t_vec3		hit;
	t_vec3		oc;
	double		k;
	t_vec3		norm;

	hit = vect_add(ray.org, vect_scale(ray.dist, ray.dir));
	oc = vect_sub(hit, form->cone.org);
	if (vect_mult_scale(form->cone.dir, oc) < 0)
		form->cone.dir = vect_scale(-1.0, form->cone.dir);
	k = 1 / cos(form->cone.theta / 2.0);
	height = norme_vect(vect_scale(k, oc));
	norm = normal_vect(vect_sub(oc, vect_scale(height, form->cone.dir)));
	return (norm);
}

static t_vec3	normal_cyl(t_ray ray, t_forms *form)
{
	t_vec3		hit;
	t_vec3		oc;
	double		height;
	t_vec3		norm;

	hit = vect_add(ray.org, vect_scale(ray.dist, ray.dir));
	oc = vect_sub(hit, form->cldre.pos);
	height = vect_mult_scale(form->cldre.dir, oc);
	norm = normal_vect(vect_sub(oc, vect_scale(height, form->cldre.dir)));
	return (norm);
}

static t_vec3	normal_sph(t_ray ray, t_forms *form)
{
	t_vec3		hit_point;

	hit_point = ft_vec3vop_r(ray.org, \
			ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	return (ft_vec3vop_r(hit_point, form->sph.ctr, '-'));
}

static t_vec3	normal_plan(t_ray ray, t_forms *form)
{
	t_ray		dummy;

	dummy = ray;
	ft_vec3normalize(&form->plan.nrml);
	if (ft_dotproduct(ray.dir, form->plan.nrml) > 0)
		return (ft_vec3sop_r(form->plan.nrml, -1, '*'));
	return (form->plan.nrml);
}

t_func_nrml		*get_nrml(void)
{
	static t_func_nrml func[NUM_FORM] = {&normal_sph, &normal_plan, \
		&normal_cone, &normal_cyl};

	return (func);
}
