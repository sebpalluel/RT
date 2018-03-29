/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_maps_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:23:53 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 18:23:59 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void fit_and_scale(double *u, double *v, t_text *text, t_text_c text_c)
{
	*u *= text->img_w;
	*v *= text->img_h;
	//SCALE FROM TEXT.SCALEX && TEXT>SCALEY
	*u *= (1 / text_c.size_x);
	*v *= (1 / text_c.size_y);
	*u = (int)*u % text->img_w;
	*v = (int)*v % text->img_h;
	if (*u < 0)
		*u += text->img_w;
	if (*v < 0)
		*v += text->img_h;
}

t_vec3 get_x_axe(t_vec3 dir)
{
	t_vec3 x_axe;

	x_axe = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(0., 1., 0.), dir, 'c'));
	if (ft_vec3norm(x_axe) == 0.0)
		x_axe = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(1., 0., 0.), dir, 'c'));
	return (x_axe);
}

void get_local_coords(t_vec3 hit, t_vec3 *coord, t_vec3 orig, t_vec3 dir)
{
	t_vec3 x_axe;
	t_vec3 y_axe;
	hit = ft_vec3vop_r(orig, hit, '-');
	coord->z = ft_vec3dot(hit, dir);
	x_axe = get_x_axe(dir);
	hit = ft_vec3vop_r(hit, ft_vec3sop_r(dir, coord->z, '*'), '-');
	y_axe = ft_vec3vop_r(x_axe, dir, 'c');
	coord->x = ft_vec3dot(hit, x_axe);
	coord->y = ft_vec3dot(hit, y_axe);
}
