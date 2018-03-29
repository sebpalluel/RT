/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 03:41:00 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 06:47:11 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display_manager.h"
#include "rt.h"

t_ray	init_ray(t_vec3 org, t_vec3 dir)
{
	t_ray ray;

	ray.org = org;
	ray.dir = ft_vec3normalize_r(dir);
	ray.dist = -1.0;
	ray.nbrefl = 0;
	ray.n = 1;
	ray.flag = 0;
	return (ray);
}

t_ray			calculate_ray(int32_t x, int32_t y, t_cam *cam, SDL_Surface *s)
{
	t_ray			ray;
	t_vec3			org;
	t_vec3			dir;

	org = ft_vec3vop_r( ft_vec3vop_r(ft_vec3sop_r(cam->rgt
					, (x - (s->w / 2.0)) / s->h, '*')
				, ft_vec3sop_r(cam->dwn, (y - (s->h / 2.0))
					/ s->h, '*'), '+'), cam->org, '+');
	dir = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3sop_r(cam->frt
					, cam->perspective_factor, '*')
				, ft_vec3vop_r(cam->org, ft_vec3vop_r(ft_vec3vop_r(
							ft_vec3sop_r(cam->rgt, (x - (s->w / 2.0))
								/ s->h, '*')
							, ft_vec3sop_r(cam->dwn, (y - s->h / 2.0)
								/ s->h, '*'), '+'), cam->org, '+'), '-'), '-'));
	ray = init_ray(org, dir);
	return (ray);
}

t_col			send_ray(t_ray ray, t_scene *scene)
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
