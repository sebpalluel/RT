/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/03/20 11:29:33 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3	point_at(t_vec3 org, t_vec3 dir, double dist)
{
	return (ft_vec3vop_r(org, ft_vec3sop_r(dir, dist, '*'), '+'));
}

double	dist_epsi(t_vec3 a, t_vec3 b)
{
	return (ft_vec3norm(ft_vec3vop_r(a, b, '-')) - 0.0001);
}

void	shadow(t_lgt lgt, t_list *objs, t_vec3 hitpoint, t_col *shad)
{
	t_vec3	dir;
	t_vec3	tmp;
	double	hit[2];
	t_mat	mat;

	dir = ft_vec3normalize_r(ft_vec3vop_r(hitpoint, lgt.vect, '-'));
	while (objs && ((hit[0] = hit_shape()[FORM(objs)->type - 1](init_ray(
		lgt.vect, dir), FORM(objs))) || 1))
	{
		if (hit[0] < (dist_epsi(hitpoint, lgt.vect)) && hit[0] > 0)
		{
			tmp = point_at(lgt.vect, dir, hit[0] + 0.0001);
			mat = get_mat_at(tmp, objs, FORM(objs)->mat);
			*shad = ft_colmult(ft_colmultscale(mat.col, mat.trsp), *shad);
			hit[1] = hit_shape()[FORM(objs)->type - 1](init_ray(tmp, dir),
				FORM(objs));
			if (hit[1] > 0 && hit[0] + hit[1] < dist_epsi(hitpoint, lgt.vect))
			{
				tmp = point_at(lgt.vect, dir, hit[0] + hit[1] - 0.0001);
				mat = get_mat_at(tmp, objs, FORM(objs)->mat);
				*shad = ft_colmult(ft_colmultscale(mat.col, mat.trsp), *shad);
			}
		}
		objs = objs->next;
	}
}
