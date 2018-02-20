/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/02/20 13:28:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_ray	init_ray(t_vect org, t_vect dir)
{
	t_ray ray;

	ray.org = org;
	ray.dir = normal_vect(dir);
	ray.dist = -1.0;
	return (ray);
}

t_vect	vect_sub(t_vect u, t_vect v)
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
	return (u);
}

double	norme_vect(t_vect u)
{
	return (sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}

t_vect	normal_vect(t_vect u)
{
	double n;

	n = norme_vect(u);
	if (n <= 0.0)
		return (init_vect(0.0, 0.0, 0.0));
	u.x = u.x / n;
	u.y = u.y / n;
	u.z = u.z / n;
	return (u);
}

double	vect_mult_scale(t_vect u, t_vect v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_col	send_ray(t_ray ray, t_setup *setup)
{
	t_list		*form;
	double		dist;
	int			i;
	int			j;

	i = 0;
	j = -1;
	form = SCN.forms;
	while (form)
	{
		if (((FORM(form)->type != 0) && (dist = hit_shape()[FORM(form)->type - 1](ray, FORM(form))) >= 0)
				&& ((ray.dist > dist || ray.dist == -1) && dist >= 0)
				&& ((j = i) || 1))
			ray.dist = dist;
		form = form->next;
		i++;
	}
	FORM(form) = env->formes;
	if (j == -1)
		return (BACK_COLOR);
	while (j--)
		FORM(form) = FORM(form)->next;
	if (FORM(form)->type != 0)
		return (intersection()[FORM(form)->type - 1](ray, FORM(form), *env));
	return (BACK_COLOR);
}
