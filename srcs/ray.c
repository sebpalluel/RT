/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/02/27 13:40:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_ray	init_ray(t_vec3 org, t_vec3 dir)
{
	t_ray ray;

	ray.org = org;
	ray.dir = normal_vect(dir);
	ray.dist = -1.0;
	return (ray);
}

t_vec3	vect_sub(t_vec3 u, t_vec3 v)
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
	return (u);
}

double	norme_vect(t_vec3 u)
{
	return (sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}

t_vec3	normal_vect(t_vec3 u)
{
	double n;

	n = norme_vect(u);
	if (n <= 0.0)
		return (init_vec3(0.0, 0.0, 0.0));
	u.x = u.x / n;
	u.y = u.y / n;
	u.z = u.z / n;
	return (u);
}

double	vect_mult_scale(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
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
