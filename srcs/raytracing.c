/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 13:23:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

static inline t_ray	calculate_ray(int32_t x, int32_t y, t_env *env)
{
	SDL_Surface		*s;
	t_ray			ray;

	s = env->surface;
	ray = init_ray(
			vect_add(
				vect_add(
					vect_scale((x - (s->w / 2.0)) / s->h, env->cam.rgt)
					, vect_scale((y - (s->h / 2.0)) / s->h, env->cam.dwn))
				, env->cam.org),
			normal_vect(
				vect_sub(
					vect_scale(env->pers, env->cam.frt)
					, vect_sub(env->cam.org
					, vect_add(
						vect_add(
							vect_scale((x - (s->w / 2.0)) / s->h, env->cam.rgt)
							, vect_scale((y - s->h / 2.0) / s->h, env->cam.dwn))
					, env->cam.org)))));
	return (ray);
}

void			*ft_raytracing(void *a) // Nathan: en fait ici c est la fonction de render
{
	t_setup		*setup;
	// TODO CameraToWorld transfo https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
	t_pix		pix;
	//t_ray		ray;
	//t_vec3 orig = {0.0, 0.0, 0.0};
	//t_color	col = {255, 0, 255};

	pthread_t	id;
	int			i;
	setup = (t_setup*)a;
	size_t		inc;

	//multVecMatrix(&orig, &ray.orig, setup->camToWorld);
	//// ft_setup_cam(setup); // fonction qui permet d'initialiser la camera suivant les donnee du parser

	id = pthread_self();
	i = -1;
	inc = SCN.height / THREAD;
	while (++i < THREAD) // permet d'identifier dans quel thread on est
		if (pthread_equal(id, setup->thrd[i]))
			break ;
	pix.y = inc * i - 1;
	pthread_mutex_lock(&setup->mutex.mutex);
	while (++pix.y <= (int)(inc * (i + 1) - 1))
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
		{
			ft_put_pixel(setup, pix.x, pix.y, \
					send_ray(calculate_ray(pix.x, px.y, setup), setup));
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
