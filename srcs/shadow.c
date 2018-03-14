/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/02/27 17:11:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_col	shadow(t_lgt *lgt, t_list *objects, t_vec3 hitpoint)
{
	t_col	shadow;
	t_vec3	dir;
	t_ray	ray;
	t_setup *setup;
	double	dist;
	double	hit;
	t_mat	mat;

	setup = get_st();
	shadow = lgt->col;
	dir = ft_vec3normalize_r(ft_vec3vop_r(hitpoint, lgt->vect, '-'));
	ray = init_ray(lgt->vect, dir);
	dist = ft_vec3norm(ft_vec3vop_r(hitpoint, lgt->vect, '-'));
	while (objects)
	{
			hit = hit_shape()[FORM(objects)->type - 1](ray, FORM(objects));
			if (hit < (dist - 0.0000001) && hit > 0)
			{
				mat = get_mat_at(ft_vec3sop_r(lgt->vect, hit, '*'), objects, FORM(objects)->mat);
				if (FORM(objects)->mat.trsp == 0 && mat.trsp == 0)
					return (setup->background);
				else if (FORM(objects)->mat.trsp == 0)
					shadow = ft_colmult(ft_colmultscale(FORM(objects)->mat.col,
						FORM(objects)->mat.trsp), shadow);
				else
				{
					shadow = ft_colmult(ft_colmultscale(mat.col,
						FORM(objects)->mat.trsp), shadow);
					hit = hit_shape()[FORM(objects)->type - 1](init_ray(ft_vec3sop_r(lgt->vect, hit + 0.00001, '*'), dir), FORM(objects));
					if (hit < (dist - 0.0000001) && hit > 0)
					{
						mat = get_mat_at(ft_vec3sop_r(lgt->vect, hit, '*'), objects, FORM(objects)->mat);
						shadow = ft_colmult(ft_colmultscale(mat.col, FORM(objects)->mat.trsp), shadow);
					}
				}
			}
		objects  = objects->next;
	}
	return (shadow);
}
