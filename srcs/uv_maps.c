/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_maps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:09:13 by esuits            #+#    #+#             */
/*   Updated: 2018/04/03 22:19:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3	uv_map_sph(t_vec3 hit, t_list *form, t_mat *mat, t_text *text)
{
	double u;
	double v;
	t_vec3 tmp;

	tmp = ft_vec3vop_r(hit, FORM(form)->sph.ctr, '-');
	u = 0.5 + atan2(tmp.z, tmp.x) / (2 * M_PI);
	tmp = ft_vec3sop_r(tmp, FORM(form)->sph.r, '/');
	v = 0.5 - asin(tmp.y) / M_PI;
	if (mat->text_m == M_TEX && text && mat)
	{
		fit_and_scale(&u, &v, text, mat->text_c);
		mat->col = text->map[(int)u + (int)v * text->img_w];
		mat->trsp = 1 - mat->col.a;
	}
	return (ft_vec3_r(u, v, 1.));
}

t_vec3	uv_map_pln(t_vec3 hit, t_list *form, t_mat *mat, t_text *text)
{
	t_vec3 x_axe;
	t_vec3 y_axe;
	double u;
	double v;

	x_axe = get_x_axe(FORM(form)->plan.nrml);
	y_axe = ft_vec3normalize_r(ft_vec3vop_r(x_axe, FORM(form)->plan.nrml, 'c'));
	u = ft_vec3dot(hit, x_axe);
	v = ft_vec3dot(hit, y_axe);
	if (mat->text_m == M_TEX && text && mat)
	{
		fit_and_scale(&u, &v, text, mat->text_c);
		mat->col = text->map[(int)u + (int)v * text->img_w];
		mat->trsp = 1 - mat->col.a;
	}
	return (ft_vec3_r(u, v, 1.));
}

t_vec3	uv_map_cyl(t_vec3 hit, t_list *form, t_mat *mat, t_text *text)
{
	double u;
	double v;
	t_vec3 coord;

	get_local_coords(hit, &coord, FORM(form)->cyl.pos, FORM(form)->cyl.dir);
	u = atan2(coord.y, coord.x) / (2 * M_PI);
	v = coord.z;
	if (mat->text_m == M_TEX && text && mat)
	{
		fit_and_scale(&u, &v, text, mat->text_c);
		mat->col = text->map[(int)u + (int)v * text->img_w];
		mat->trsp = 1 - mat->col.a;
	}
	return (ft_vec3_r(u, v, 1.));
}

t_vec3	uv_map_cone(t_vec3 hit, t_list *form, t_mat *mat, t_text *text)
{
	t_vec3 coord;
	double u;
	double v;

	get_local_coords(hit, &coord, FORM(form)->cone.org, FORM(form)->cone.dir);
	u = atan2(coord.y, coord.x) / (2 * M_PI);
	v = coord.z;
	if (mat->text_m == M_TEX && text && mat)
	{
		fit_and_scale(&u, &v, text, mat->text_c);
		mat->col = text->map[(int)u + (int)v * text->img_w];
		mat->trsp = 1 - mat->col.a;
	}
	return (ft_vec3_r(u, v, 1.));
}
