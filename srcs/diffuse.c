/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/02/28 15:20:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double				hit_obj(t_lgt *lgt, t_ray camray, t_list *form, t_list *obj)
{
	double		dist;
	t_vec3		dir;
	t_ray		ray;
	t_list		*ombre;
	t_setup		*setup;

	setup = get_st();
	dir = ft_vec3vop_r(ft_vec3vop_r(camray.org, ft_vec3sop_r(camray.dir, camray.dist, '*'), '+'),
			lgt->vect, '-');
	ray = init_ray(lgt->vect, ft_vec3normalize_r(dir));
	ombre = NULL;
	while (form)
	{
		if ((/*!FORM(form)->mat.trsp &&*/ (dist = hit_shape()[FORM(form)->type - 1](ray, FORM(form))) >= 0) && ((ray.dist > dist || ray.dist == -1) && dist >= 0))
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

double	phong(t_ray ray, t_col col, t_vec3 norm, t_list *light)
{
	double	refl;
	t_vec3	phongdir;
	t_vec3	lgtdir;
	double	phongterm;

	//if (LGT(light)->type == 0)
		lgtdir = ft_vec3normalize_r(ft_vec3vop_r(LGT(light)->vect,
				ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+'), '-'));
	//else
		//lgtdir = LGT(light)->dir;
//	printf("%zu\n", LGT(light)->type);
	refl = 2.0 * ft_vec3dot(lgtdir, norm);
	phongdir = ft_vec3vop_r(lgtdir, ft_vec3sop_r(norm, refl, '*'), '-');
	phongterm = ft_vec3dot(phongdir, ray.dir);
	if (phongterm < 0.0)
		phongterm = 0.0;
	phongterm = (col.s * pow(phongterm, 50.0) * LGT(light)->col.s); //pas tres physiquement possible une lumieère avec un specule
	return (phongterm);
}

double	lambert(t_ray ray, t_vec3 norm, t_list *lgt)
{
	return (ft_vec3dot(ft_vec3normalize_r(ft_vec3vop_r(LGT(lgt)->vect,
						ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+'), '-')), norm));
}

t_col	diffuse(t_vec3 norm, t_list *form, t_ray ray, t_mat mat_obj)
{
	double		lmbrt;
	double		dist;
	t_col		col;
	t_col		spec;
	t_col		refl;
	t_col		refract;
	t_col		shad;
	t_col		glob;
	t_ray		refract_ray;
	t_list		*lgt;
	t_setup		*setup;
	t_vec3		hit;
	t_mat hit_mat;

	setup = get_st();
	col = setup->background;
	hit = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	glob = col;
	if (ray.flag < 0)
	{
		if (mat_obj.trsp)
			glob = ft_colinterpol(global_illum(ray, norm, hit),global_illum(ray, ft_vec3sop_r(norm, -1, '*'), hit), mat_obj.trsp);
		else
			glob = global_illum(ray, norm, hit);
	}
	lgt = SCN.lgts;
	refl = col;
	spec = col;
	refract = mat_obj.col;
	if (mat_obj.trsp != 0 && (ray.nbrefl < (int)SCN.refl_max))
	{
		if (ft_vec3dot(norm, ray.dir) > 0)
		{
			refract_ray = refraction(ray, ft_vec3sop_r(norm, -1, '*'), 1);
			if (ft_vec3norm(refract_ray.dir) != 0)
				refract = send_ray(refract_ray, setup);
			else
				refract = send_ray(reflexion(ray, ft_vec3sop_r(norm, -1, '*')), setup);
		}
		else
		{
			refract_ray = refraction(ray, norm, mat_obj.n);
			if (ft_vec3norm(refract_ray.dir) != 0)
				refract = send_ray(refract_ray, setup);
			else
				refract = send_ray(reflexion(ray, norm), setup);
		}
	}
	if (ray.nbrefl < (int)SCN.refl_max && mat_obj.refl != 0)
		refl = send_ray(reflexion(ray, norm), setup);
	while (lgt)
	{
		shad = shadow(LGT(lgt), SCN.forms, hit);
	//	shad = LGT(lgt)->col;
//		(void)form;
		lmbrt = lambert(ray, norm, lgt);
		if (lmbrt < 0.0)
			lmbrt = 0;
		dist = ft_vec3norm(ft_vec3vop_r(hit, LGT(lgt)->vect, '-'));
		dist *= dist;
		hit_mat = get_mat_at(hit, form, mat_obj);
//		dist = 1;
		col = ft_coladd(ft_colinterpol(setup->background, ft_colmultscale(
							ft_colmult(hit_mat.col, shad), 4 * SCN.expo / dist), lmbrt * lmbrt), col);
		spec = ft_coladd(spec, ft_colmultscale(ft_colinterpol(setup->background,
						shad, phong(ray, hit_mat.col, norm, lgt)), 4 * SCN.expo / dist));
		lgt = lgt->next;
	}
	return (ft_coladd(ft_colinterpol(ft_colinterpol(ft_coladd(spec, col), ft_colmult(refract, mat_obj.col), mat_obj.trsp), refl, mat_obj.refl), glob));//, 0.5));
//	return (ft_colinterpol(ft_colinterpol(ft_coladd(spec, col), ft_colmult(refract, mat_obj.col), mat_obj.trsp), refl, mat_obj.refl));
}
