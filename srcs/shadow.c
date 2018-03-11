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

	setup = get_st();
	shadow = lgt->col;
	dir = ft_vec3vop_r(hitpoint, lgt->vect, '-');
	ray = init_ray(lgt->vect, ft_vec3normalize_r(dir));
	dist = ft_vec3norm(ft_vec3vop_r(hitpoint, lgt->vect, '-'));
	while (objects)
	{
			hit = hit_shape()[FORM(objects)->type - 1](ray, FORM(objects));
			if (hit < (dist - 0.0000001) && hit > 0)
				shadow = ft_colmult(ft_colmultscale(FORM(objects)->mat.col,
					FORM(objects)->mat.trsp), shadow);
		objects  = objects->next;
	}
	return (shadow);
}