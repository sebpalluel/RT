/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/03/29 16:14:08 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_col	shadow(t_lgt *lgt, t_list *objects, t_vec3 hitpoint, t_scene *scene)
{
	t_col	shadow;
	t_vec3	dir;
	t_vec3	tmp;
	t_ray	ray;
	double	dist;
	double	hit;
	double	hit2;
	t_mat	mat;

	shadow = lgt->col;
	dir = ft_vec3normalize_r(ft_vec3vop_r(hitpoint, lgt->vect, '-'));
	ray = init_ray(lgt->vect, dir);
	dist = ft_vec3norm(ft_vec3vop_r(hitpoint, lgt->vect, '-'));
	while (objects)
	{
			hit = hit_shape()[FORM(objects)->type - 1](ray, FORM(objects));
			if (hit < (dist - 0.001) && hit > 0)
			{
				tmp = ft_vec3vop_r(lgt->vect, ft_vec3sop_r(dir, hit + 0.001, '*'),'+');
				mat = get_mat_at(tmp, objects, FORM(objects)->mat);
				if (FORM(objects)->mat.trsp != 0)
					mat.trsp = FORM(objects)->mat.trsp;
				if (mat.trsp == 0)
					return (scene->background);
				else
				{
					shadow = ft_colmult(ft_colmultscale(mat.col,
						mat.trsp), shadow);
					hit2 = hit_shape()[FORM(objects)->type - 1](init_ray(tmp, dir), FORM(objects));
					if (hit2 > 0 && hit + hit2 < dist - 0.001)
					{
						tmp = ft_vec3vop_r(lgt->vect, ft_vec3sop_r(dir, hit + hit2 - 0.001, '*'),'+');
						mat = get_mat_at(tmp, objects, FORM(objects)->mat);
						shadow = ft_colmult(ft_colmultscale(mat.col, mat.trsp), shadow);
					}
				}
			}
		objects  = objects->next;
	}
	return (shadow);
}
