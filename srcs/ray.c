/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 03:32:32 by esuits            #+#    #+#             */
/*   Updated: 2018/02/20 19:30:18 by psebasti         ###   ########.fr       */
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
	form = SCN.forms;
	if (j == -1)
		return (setup->background);
	while (j--)
		form = form->next;
	if (FORM(form)->type != 0)
		return (intersection()[FORM(form)->type - 1](ray, form, setup));
	return (setup->background);
}
