/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/02/23 11:03:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				hit_obj(t_lgt *lgt, t_ray camray, t_list *form, t_list *obj)
{
	double		dist;
	t_vec3		dir;
	t_ray		ray;
	t_list		*ombre;
	t_setup		*setup;

	setup = get_st();
	dir = vect_sub(vect_add(camray.org, vect_scale(camray.dist, camray.dir)), 
			lgt->vect);
	ray = init_ray(lgt->vect, normal_vect(dir));
	ombre = NULL;
	while (form)
	{
		if (((FORM(form)->type != 0) &&
					(dist = hit_shape()[FORM(form)->type - 1](ray, FORM(form))) >= 0) &&
				((ray.dist > dist || ray.dist == -1) && dist >= 0))
		{
			ray.dist = dist;
			ombre = form;
		}
		form = form->next;
	}
	//if (ombre && !ft_memcmp(FORM(ombre), FORM(obj), sizeof(t_forms)))
	if (ombre && ombre == obj)
		return (0);
	return (1);
}

double	phong(t_ray ray, t_col col, t_vec3 norm, t_list *light)
{
	double	refl;
	t_vec3	phongdir;
	t_vec3	lgtdir;
	double	phongterm;

	lgtdir = normal_vect(vect_sub(LGT(light)->vect,
				vect_add(ray.org, vect_scale(ray.dist, ray.dir))));
	refl = 2.0 * vect_mult_scale(lgtdir, norm);
	phongdir = vect_sub(lgtdir, vect_scale(refl, norm));
	phongterm = vect_mult_scale(phongdir, ray.dir);
	if (phongterm < 0.0)
		phongterm = 0.0;
	phongterm = (col.s * pow(phongterm, 50.0) * LGT(light)->col.s);
	return (phongterm);
}

double	lambert(t_ray ray, t_vec3 norm, t_list *lgt)
{
	return (vect_mult_scale(normal_vect(vect_sub(LGT(lgt)->vect,
						vect_add(ray.org, vect_scale(ray.dist, ray.dir)))), norm));
}

t_col	diffuse(t_setup *setup, t_list *form, t_ray ray, t_col col_obj)
{
	double		lmbrt;
	t_col		col;
	t_col		spec;
	t_list		*lgt;

	col = setup->background;
	spec = col;
	lgt = SCN.lgts;
	while (lgt)
	{
		if (hit_obj(LGT(lgt), ray, SCN.forms, form))
		{
			lgt = lgt->next;
			continue ;
		}
		lmbrt = lambert(ray, FORM(form)->norm, lgt);
		if (lmbrt < 0.0)
			lmbrt = 0;
		col = addcol(interpolcol(setup->background, mult_scale_col(SCN.expo, multcol(
							col_obj, LGT(lgt)->col)), lmbrt * lmbrt), col);
		spec = addcol(spec, mult_scale_col(SCN.expo, interpolcol(setup->background,
						LGT(lgt)->col, phong(ray, col_obj, FORM(form)->norm,
							lgt))));
		lgt = lgt->next;
	}
	return (addcol(spec, col));
}
