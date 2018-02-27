/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 19:25:41 by psebasti         ###   ########.fr       */
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

	hit = ft_vec3add_r(ray.org, ft_vec3multscale_r(ray.dir, ray.dist));
	oc = ft_vec3sub_r(hit, form->cone.org);
	if (ft_vec3dot(form->cone.dir, oc) < 0)
		form->cone.dir = ft_vec3multscale_r(form->cone.dir, -1.);
	k = 1 / cos(form->cone.theta / 2.0);
	height = ft_vec3norm(ft_vec3multscale_r(oc, k));
	norm = ft_vec3normalize_r(ft_vec3sub_r(oc, ft_vec3multscale_r(form->cone.dir, height)));
	return (norm);
}

static t_vec3	normal_cyl(t_ray ray, t_forms *form)
{
	t_vec3		hit;
	t_vec3		oc;
	double		height;
	t_vec3		norm;

	hit = ft_vec3add_r(ray.org, ft_vec3multscale_r(ray.dir, ray.dist));
	oc = ft_vec3sub_r(hit, form->cldre.pos);
	height = ft_vec3dot(form->cldre.dir, oc);
	norm = ft_vec3normalize_r(ft_vec3sub_r(oc, ft_vec3multscale_r(form->cldre.dir, height)));
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
