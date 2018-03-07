/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/07 19:27:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

# define EFFECT		1
# define EFFECT_N	2

static inline t_ray	calculate_ray(int32_t x, int32_t y, t_setup *setup)
{
	t_ray			ray;
	t_cam			cam;
	t_vec3			org;
	t_vec3			dir;

	cam = *SCN.cur_cam;
	org = ft_vec3vop_r( ft_vec3vop_r(ft_vec3sop_r(cam.rgt, \
					(x - (SCN.width/ 2.0)) / SCN.height, '*'), \
				ft_vec3sop_r(cam.dwn, (y - (SCN.height / 2.0)) \
					/ SCN.height, '*'), '+'), cam.org, '+');
	dir = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3sop_r(cam.frt, SCN.pers, '*')\
				, ft_vec3vop_r(cam.org, ft_vec3vop_r(ft_vec3vop_r(\
							ft_vec3sop_r(cam.rgt, (x - (SCN.width / 2.0)) \
								/ SCN.height, '*'), \
							ft_vec3sop_r(cam.dwn, (y - SCN.height / 2.0) \
								/ SCN.height, '*'), '+'), cam.org, '+'), '-'),\
				'-'));
	ray = init_ray(org, dir);
	return (ray);
}

void			*ft_raytracing(void *a)
{
	t_setup		*setup;
	t_pix		pix;
	pthread_t	id;
	size_t		thread_n;
	size_t		inc;

	setup = (t_setup *)a;
	id = pthread_self();
	inc = SCN.height / THREAD;
	thread_n = ft_get_thread_n(setup);
	pix.y = inc * thread_n - 1;
	//pthread_mutex_lock(&setup->mutex.mutex);
	while (++pix.y <= (int)(inc * (thread_n + 1) - 1))
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
		{
			if (!EFFECT)
				ft_put_pixel(setup, pix.x, pix.y, \
						ft_coltoi(send_ray(calculate_ray(pix.x, pix.y, setup), \
								setup)));
			else
				ft_put_pixel(setup, pix.x, pix.y, \
						ft_coltoi(effects()[EFFECT_N]((double)pix.x, (double)\
								pix.y, (double)pix.z)));
		}
	}
	//pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
