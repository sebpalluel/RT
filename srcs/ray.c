/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/02/27 17:11:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_ray	init_ray(t_vec3 org, t_vec3 dir)
{
	t_ray ray;

	ray.org = org;
	ray.dir = ft_vec3normalize_r(dir);
	ray.dist = -1.0;
	ray.nbrefl = 0;
	ray.n = 1;
	return (ray);
}

t_col	send_ray(t_ray ray, t_setup *setup)
{
	t_list		*ptr;
	t_list		*nearest;
	double		dist;

	ptr = SCN.forms;
	nearest = NULL;
	while (ptr)
	{
		if (((FORM(ptr)->type != 0) && (dist = hit_shape()[FORM(ptr)->type - 1](ray, FORM(ptr))) >= 0)
				&& ((ray.dist > dist || ray.dist == -1) && dist >= 0))
		{
			nearest = ptr;
			ray.dist = dist;

		}
	ptr = ptr->next;
	}
	if (!nearest)
		return (setup->background);
	if (FORM(nearest)->type != 0)
		return (intersection()[FORM(nearest)->type - 1](ray, nearest, setup));
	return (setup->background);
}