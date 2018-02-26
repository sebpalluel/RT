/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 15:49:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

static inline t_ray	calculate_ray(int32_t x, int32_t y, t_setup *setup)
{
	t_ray			ray;
	t_cam			*cam;
	t_list			*cams;

	//TODO will be hable to handle which cam is it
	cams = SCN.cams;
	cam = CAM(cams);
	ray = init_ray(
			vect_add(
				vect_add(
					vect_scale((x - (SCN.width/ 2.0)) / SCN.height, cam->rgt)
					, vect_scale((y - (SCN.height / 2.0)) / SCN.height, cam->dwn))
				, cam->org),
			normal_vect(
				vect_sub(
					vect_scale(SCN.pers, cam->frt)
					, vect_sub(cam->org
					, vect_add(
						vect_add(
							vect_scale((x - (SCN.width / 2.0)) / SCN.height, cam->rgt)
							, vect_scale((y - SCN.height / 2.0) / SCN.height, cam->dwn))
					, cam->org)))));
	return (ray);
}

void			*ft_raytracing(void *a) // Nathan: en fait ici c est la fonction de render
{
	t_setup		*setup;
	t_pix		pix;
	pthread_t	id;
	int			i;
	size_t		inc;

	setup = (t_setup *)a;
	id = pthread_self();
	i = -1;
	inc = SCN.height / THREAD;
	while (++i < THREAD) // permet d'identifier dans quel thread on est
		if (pthread_equal(id, setup->thrd[i]))
			break ;
	pix.y = inc * i - 1;
	//pthread_mutex_lock(&setup->mutex.mutex);
	while (++pix.y <= (int)(inc * (i + 1) - 1))
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
		{
			ft_put_pixel(setup, pix.x, pix.y, \
					coltoi(send_ray(calculate_ray(pix.x, pix.y, setup), setup)));
		}
	}
	//pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
