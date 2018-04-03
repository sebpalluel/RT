/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/03/20 11:29:41 by psebasti         ###   ########.fr       */
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

t_col	refract_col(t_mat mat, t_vec3 norm, t_setup *setup, t_ray ray)
{
	t_col refract;
	t_ray refract_ray;

	refract = mat.col;
	if ((mat.trsp != 0) && (ray.nbrefl < SCN.refl_max))
	{
		if (ft_vec3dot(ft_vec3normalize_r(norm), ray.dir) > 0)
		{
			refract_ray = refraction(ray, ft_vec3sop_r(norm, -1, '*'), 1);
			if (ft_vec3norm(refract_ray.dir) != 0)
				refract = send_ray(refract_ray, setup);
			else
				refract = send_ray(reflexion(ray,
					ft_vec3sop_r(norm, -1, '*')), setup);
		}
		else
		{
			refract_ray = refraction(ray, norm, mat.n);
			if (ft_vec3norm(refract_ray.dir) != 0)
				refract = send_ray(refract_ray, setup);
			else
				refract = send_ray(reflexion(ray, norm), setup);
		}
	}
	return (refract);
}

t_col	reflex_col(t_mat mat, t_vec3 norm, t_setup *setup, t_ray ray)
{
	t_col refl;

	refl = setup->background;
	if (ray.nbrefl < (int)SCN.refl_max && mat.refl != 0)
		refl = send_ray(reflexion(ray, norm), setup);
	return (refl);
}

t_col	diff_col(t_mat mat, t_vec3 norm, t_lgt lgt, t_ray ray)
{
	t_col col;
	t_vec3 hit;
	t_setup *setup;
	t_col shad;
	double dist;

	shad = lgt.col;
	setup = get_st();
	shadow(lgt, SCN.forms, hit, &shad);
	hit = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	dist = ft_vec3norm(ft_vec3vop_r(hit, lgt.vect, '-'));
	dist = dist * dist;
	col = ft_colinterpol(setup->background, ft_colmultscale(
			ft_colmult(mat.col, shad), 4 * SCN.expo / dist),
			lambert(ray, norm, lgt));
	col = ft_coladd(col, ft_colmultscale(ft_colinterpol(setup->background,
			shad, phong(ray, mat, norm, lgt)), 4 * SCN.expo / dist));
	return (col);
}

t_col	glob_col(t_vec3 hit, t_vec3 norm, t_setup *setup, t_ray ray)
{
	t_col glob;

	glob = setup->background;
	if (ray.flag < (GLOBAL_ILL && 1))
		glob = global_illum(ray, norm, hit);
	return (glob);
}

t_col	diffuse(t_vec3 norm, t_list *form, t_ray ray, t_mat mat_obj)
{
	t_col		col;
	t_list		*lgt;
	t_setup		*setup;
	t_vec3		hit;
	t_mat		hit_mat;

	setup = get_st();
	lgt = SCN.lgts;
	hit = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	hit_mat = get_mat_at(hit, form, mat_obj);
	col = amb_light(hit_mat.col, norm, ray.dir, SCN.amb_light);
	while (lgt)
	{
		col = ft_coladd(diff_col(hit_mat, norm, *LGT(lgt), ray), col);
		lgt = lgt->next;
	}
	col = ft_colinterpol(ft_colinterpol(ft_coladd(col, glob_col(hit, norm, setup, ray)),
		ft_colmult(refract_col(hit_mat, norm, setup, ray), hit_mat.col),
		hit_mat.trsp), reflex_col(hit_mat, norm, setup, ray), hit_mat.refl);
	return (col);
}
