/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/03/14 18:16:09 by psebasti         ###   ########.fr       */
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
		if (((dist = hit_shape()[FORM(form)->type - 1](ray, FORM(form))) >= 0) && ((ray.dist > dist || ray.dist == -1) && dist >= 0))
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


	lgtdir = ft_vec3normalize_r(ft_vec3vop_r(LGT(light)->vect,
				ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+'), '-'));
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

t_vec3		normal_distortion(t_list *form, t_vec3 hit, t_vec3 norm)
{
	//t_vec3	vec3;
	//double	e;

	//e = 0.00002323;
	(void)form;
	//vec3 = ft_vec3_r(norm.x + hit.x, 50 * norm.y + 100 * hit.y, norm.z + hit.z);
	//vec3.x = ft_wood(ft_vec3_r(vec3.x - e, vec3.y, vec3.z)) - \
	//		 ft_wood(ft_vec3_r(vec3.x + e, vec3.y, vec3.z));
	//vec3.y = ft_wood(ft_vec3_r(vec3.x, vec3.y - e, vec3.z)) - \
	//		 ft_wood(ft_vec3_r(vec3.x, vec3.y + e, vec3.z));
	//vec3.z = ft_wood(ft_vec3_r(vec3.x, vec3.y, vec3.z - e)) - \
	//		 ft_wood(ft_vec3_r(vec3.x, vec3.y, vec3.z + e));
	//return (ft_vec3add_r(norm, vec3));
	t_vec3 temp;
	double bump;

	bump = 0.0001;
	float noiseCoefx = (ft_perlin(ft_vec3_r(0.1 * (hit.x), 0.1 * (hit.y),0.1 * (hit.z))));
	float noiseCoefy = (ft_perlin(ft_vec3_r(0.1 * (hit.y), 0.1 * (hit.z),0.1 * (hit.x))));
	float noiseCoefz = (ft_perlin(ft_vec3_r(0.1 * (hit.z), 0.1 * (hit.x),0.1 * (hit.y))));

	norm.x = (1.0f - bump ) * norm.x + bump * noiseCoefx; 
	norm.y = (1.0f - bump ) * norm.y + bump * noiseCoefy; 
	norm.z = (1.0f - bump ) * norm.z + bump * noiseCoefz; 

	temp = ft_vec3mult_r(norm, norm);
	if (!(temp.x == 0.0f && temp.y == 0. && temp.z == 0.))
	{
		temp = ft_vec3_r(ft_invsqrt(temp.x), ft_invsqrt(temp.y), ft_invsqrt(temp.z));
		norm = ft_vec3mult_r(temp, norm);
	}
	return (norm);
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
	t_vec3		ref;

	setup = get_st();
	lgt = SCN.lgts;
	hit = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	glob = setup->background;
	refl = setup->background;
	spec = setup->background;
	refract = mat_obj.col;
	hit_mat = get_mat_at(hit, form, mat_obj);
	//if (FORM(form)->type == PLN)
	//	norm = normal_distortion(form, hit, norm);
	ref = ft_vec3multscale_r(hit, 100.);
	norm = ft_vec3addscale_r(norm, ft_perlin(ref) / 100.);
	col = amb_light(hit_mat.col, norm, ray.dir, SCN.amb_light);
	if (mat_obj.trsp != 0 && (ray.nbrefl < (int)SCN.refl_max))
	{
		if (ft_vec3dot(ft_vec3normalize_r(norm), ray.dir) > 0)
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
	if (ray.flag < 0)
		glob = global_illum(ray, norm, hit, form);
	while (lgt)
	{
		shad = shadow(LGT(lgt), SCN.forms, hit);
		//shad = LGT(lgt)->col;
		lmbrt = lambert(ray, norm, lgt);
		if (lmbrt < 0.0)
			lmbrt = 0;
		dist = ft_vec3norm(ft_vec3vop_r(hit, LGT(lgt)->vect, '-'));
		dist *= dist;

		//		dist = 1;
		col = ft_coladd(ft_colinterpol(setup->background, ft_colmultscale(
						ft_colmult(hit_mat.col, shad), 4 * SCN.expo / dist), lmbrt * lmbrt), col);
		spec = ft_coladd(spec, ft_colmultscale(ft_colinterpol(setup->background,
						shad, phong(ray, hit_mat.col, norm, lgt)), 4 * SCN.expo / dist));
		lgt = lgt->next;
	}
	return (ft_colinterpol(ft_colinterpol(ft_coladd(spec, ft_coladd(col, glob)), ft_colmult(refract, mat_obj.col), mat_obj.trsp), refl, mat_obj.refl));
}
