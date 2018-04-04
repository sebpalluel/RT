/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchalot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:23:01 by nchalot           #+#    #+#             */
/*   Updated: 2018/04/04 10:23:21 by nchalot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3	new_dir(t_ray ray, t_vec3 vect)
{
	return (ft_vec3normalize_r(ft_vec3vop_r(ft_vec3vop_r(ray.org,
		ft_vec3sop_r(ray.dir, ray.dist, '*'), '+'),
			vect, '-')));
}

double	hit_obj(t_lgt *lgt, t_ray camray, t_list *form, t_list *obj)
{
	double		dist;
	t_vec3		dir;
	t_ray		ray;
	t_list		*ombre;
	t_setup		*setup;

	setup = get_st();
	dir = new_dir(camray, lgt->vect);
	ray = init_ray(lgt->vect, dir);
	ombre = NULL;
	while (form)
	{
		if (((dist = hit_shape()[FORM(form)->type - 1](ray, FORM(form)))
			>= 0) && ((ray.dist > dist || ray.dist == -1) && dist >= 0))
		{
			ray.dist = dist;
			ombre = form;
		}
		form = form->next;
	}
	if (ombre && ombre == obj)
		return (ray.dist);
	return (-1);
}

double	phong(t_ray ray, t_mat mat, t_vec3 norm, t_lgt light)
{
	double	refl;
	t_vec3	phongdir;
	t_vec3	lgtdir;
	double	phongterm;

	lgtdir = ft_vec3sop_r(new_dir(ray, light.vect), -1, '*');
	refl = 2.0 * ft_vec3dot(lgtdir, norm);
	phongdir = ft_vec3vop_r(lgtdir, ft_vec3sop_r(norm, refl, '*'), '-');
	phongterm = ft_vec3dot(phongdir, ray.dir);
	if (phongterm < 0.0)
		phongterm = 0.0;
	phongterm = (mat.s * pow(phongterm, 50.0));
	return (phongterm);
}

double	lambert(t_ray ray, t_vec3 norm, t_lgt lgt)
{
	double	lmbrt;

	lmbrt = ft_vec3dot(ft_vec3normalize_r(ft_vec3vop_r(lgt.vect,
		ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist,
			'*'), '+'), '-')), norm);
	if (lmbrt < 0.0)
		lmbrt = 0;
	return (lmbrt);
}
