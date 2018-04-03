/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/02 19:10:13 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline t_ray	calculate_ray(int32_t x, int32_t y, t_setup *setup)
{
	t_ray			ray;
	t_cam			cam;
	t_vec3			org;
	t_vec3			dir;

	cam = *SCN.cur_cam;
	org = ft_vec3vop_r(ft_vec3vop_r(ft_vec3sop_r(cam.rgt,
			(x - (SCN.width / 2.0)) / SCN.height, '*'),
			ft_vec3sop_r(cam.dwn, (y - (SCN.height / 2.0))
			/ SCN.height, '*'), '+'), cam.org, '+');
	dir = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3sop_r(cam.frt, SCN.pers, '*')
			, ft_vec3vop_r(cam.org, ft_vec3vop_r(ft_vec3vop_r(
			ft_vec3sop_r(cam.rgt, (x - (SCN.width / 2.0)) / SCN.height, '*'),
			ft_vec3sop_r(cam.dwn, (y - SCN.height / 2.0)
			/ SCN.height, '*'), '+'), cam.org, '+'), '-'), '-'));
	ray = init_ray(org, dir);
	return (ray);
}

t_col				ft_col_map(t_col col)
{
	if (col.r > 0)
		col.r = col.r / (col.r + 1);
	else
		col.r = 0;
	if (col.g > 0)
		col.g = col.g / (col.g + 1);
	else
		col.g = 0;
	if (col.b > 0)
		col.b = col.b / (col.b + 1);
	else
		col.b = 0;
	return (col);
}

void				*ft_raytracing(void *a)
{
	t_setup		*setup;
	t_pix		pix;
	int			thread_n;
	int			inc;
	int			to_y;

	setup = (t_setup *)a;
	inc = SCN.height / THREAD;
	thread_n = ft_get_thread_n(setup);
	pix.y = inc * thread_n - 1;
	to_y = (thread_n == THREAD - 1 ? SCN.height - 1 :
			(inc * (thread_n + 1) - 1));
	while (++pix.y <= to_y)
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
			ft_put_pixel(setup, pix.x, pix.y,
				ft_coltoi(ft_col_map(send_ray(
				calculate_ray(pix.x, pix.y, setup), setup))));
	}
	pthread_exit(NULL);
}
