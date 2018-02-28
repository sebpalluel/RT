/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 17:19:05 by nchalot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

t_forms			*ft_trace(t_ray *ray, t_setup *setup)
{
	t_forms		*form;
	double		t_near;
	double		t;
	t_list		*list;

	t = MAX_INT;
	t_near = ray->dist == -1 ? MAX_INT : ray->dist;
	form = NULL;
	list = SCN.forms;
	while (list)
	{
		ray->hit = FALSE;
		if (FORM(list)->type <= 3)
		{
			ray->hit = param()[FORM(list)->type](ray, FORM(list), &t);
			if ((ray->hit == TRUE && t < t_near))
			{
				t_near = t;
				ray->dist = t_near;
				form = FORM(list);
			}
		}
		list = list->next;
	}
	return (form);
}

t_col			ft_cast_ray(t_ray ray, t_setup *setup)
{
	t_forms		*form;
	t_lgt		*light;
	t_hit		hit;
	t_ray		sdw_ray;

	light = LGT(SCN.lgts);
	hit.col = setup->background;
	form = NULL;
	if ((form = ft_trace(&ray, setup)))
	{
		hit.pos = ft_vec3vop_r(ray.org, \
				ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
		hit.nrml = get_nrml()[form->type](ray, form);
		illuminate(&hit, form->mat, light);
		init_sdw_ray(&sdw_ray, light, &hit);
		if (ft_trace(&sdw_ray, setup))
			hit.col = ft_colmultscale(hit.col, 0.);
	}
	return (hit.col);
}

static	void	ft_init_primray(t_setup *setup, t_pix pix, t_ray *ray)
{
	double		scale;
	double		aspect_ratio;
	t_vec3		dir;

	scale = tan(DEG2RAD((FOV * 0.5)));
	aspect_ratio = SCN.width / (double)SCN.height;
	dir.x = (2 * (pix.x + 0.5) / (double)SCN.width - 1) * aspect_ratio * scale;
	dir.y = (1 - 2 * (pix.y + 0.5) / (double)SCN.height) * scale;
	dir.z = -1;
	ft_vec3normalize(&dir);
	mult_dir_matrix(&dir, &ray->dir, setup->camtoworld);
	ft_vec3normalize(&ray->dir);
	ray->dist = -1;
}

void			*ft_raytracing(void *cam)
{
	t_setup		*setup;
	t_pix		pix;
	t_ray		ray;
	size_t		thread_n;
	size_t		inc;

	setup = get_st();
	(void)(cam);
	mult_vec3_matrix(ft_vec3_r(0., 0., 0.), &ray.org, setup->camtoworld);
	inc = SCN.height / THREAD;
	thread_n = ft_get_thread_n(setup);
	pix.y = inc * thread_n - 1;
	pthread_mutex_lock(&setup->mutex.mutex);
	while (++pix.y <= (int)(inc * (thread_n + 1) - 1))
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
		{
			ft_init_primray(setup, pix, &ray);
			ft_put_pixel(setup, pix.x, pix.y, \
					ft_coltoi(ft_cast_ray(ray, setup)));
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
