/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 19:16:55 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

double			max(double a, double b)
{
	return (a >= b ? a : b);
}

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

t_col			mult_scale_col_limited(double t, t_col col)
{
	col.r = col.r * t;
	col.g = col.g * t;
	col.b = col.b * t;
	if (col.r > 1)
		col.r = 1;
	if (col.g > 1)
		col.g = 1;
	if (col.b > 1)
		col.b = 1;
	return (col);
}

void			illuminate(t_hit *hit, t_mat mat, t_lgt *light)
{
	float		r2;
	t_vec3		lightdir;
	double		dist;
	double		lambert;

	lightdir = ft_vec3vop_r(light->vect, hit->pos, '-');
	r2 = ft_dotproduct(lightdir, lightdir);
	ft_vec3normalize(&lightdir);
	dist = sqrt(r2);
	lambert = max(0, ft_dotproduct(hit->nrml, lightdir));
	hit->col = mult_scale_col_limited(lambert, \
			mult_scale_col_limited(mat.diffuse, mat.col));
}

void			init_sdw_ray(t_ray *sdw_ray, t_lgt *light, t_hit *hit)
{
	double bias;
	t_vec3 lightdir;
	t_vec3 tmp;

	bias = 0.0001;
	lightdir = ft_vec3vop_r(light->vect, hit->pos, '-');
	sdw_ray->org = ft_vec3vop_r(hit->pos, \
			ft_vec3sop_r(hit->nrml, bias, '*'), '+');
	sdw_ray->dir = ft_vec3normalize_r(lightdir);
	tmp = ft_vec3vop_r(hit->pos, light->vect, '-');
	sdw_ray->dist = sqrt(ft_dotproduct(tmp, tmp));
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

void			mult_dir_matrix(t_vec3 *src, t_vec3 *dst, double **x)
{
	double		a;
	double		b;
	double		c;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2];
	dst->x = a;
	dst->y = b;
	dst->z = c;
}

void			mult_vec3_matrix(t_vec3 src, t_vec3 *dst, double **x)
{
	double		a;
	double		b;
	double		c;
	double		w;

	a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0] + x[3][0];
	b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1] + x[3][1];
	c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2] + x[3][2];
	w = src.x * x[0][3] + src.y * x[1][3] + src.z * x[2][3] + x[3][3];
	dst->x = a / w;
	dst->y = b / w;
	dst->z = c / w;
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
	mult_dir_matrix(&dir, &ray->dir, setup->camToWorld);
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
	mult_vec3_matrix(((t_cam *)cam)->org, &ray.org, setup->camToWorld);
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
