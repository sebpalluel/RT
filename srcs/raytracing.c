/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 13:41:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>


double max(double a, double b) {
	return (a >= b ? a : b);
}

t_forms 		*ft_trace(t_ray *ray, t_setup *setup)
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

t_col mult_scale_col_limited(double t, t_col col)
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

t_col illuminate(t_vec3 *p, t_vec3 *hit_nrml, t_mat *mat, t_lgt *light)
{
	float r2;
	t_vec3 lightdir;
	double dist;

	lightdir = ft_vec3vop_r(light->vect, *p, '-');
	r2 =  ft_dotproduct(lightdir,lightdir) ;
	ft_vec3normalize(&lightdir);
	dist = sqrt(r2);
	double lambert =  max(0, ft_dotproduct(*hit_nrml, lightdir));
	t_col hit_col = mult_scale_col_limited(lambert * lambert *4 ,mult_scale_col_limited(mat->diffuse, mat->col));
	return (hit_col);
}

t_col ft_cast_ray(t_ray ray, t_setup *setup)
{
	t_forms *form;
	t_lgt *light;
	t_hit	hit;

	light = LGT(SCN.lgts);
	hit.col = setup->background;
	form = NULL;
	if ((form = ft_trace(&ray, setup)))
	{
		hit.pos = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
		hit.nrml = get_nrml()[form->type](ray, form);
		if (form->type == SPH)
			hit.col = illuminate(&hit.pos, &hit.nrml, &form->sph.mat, light);
		else if (form->type == PLN)
			hit.col = illuminate(&hit.pos, &hit.nrml, &form->plan.mat, light);
		else if (form->type == CON)
			hit.col = illuminate(&hit.pos, &hit.nrml, &form->cone.mat, light);
		else if (form->type == CYL)
			hit.col = illuminate(&hit.pos, &hit.nrml, &form->cldre.mat, light);
		t_vec3 light_dir = ft_vec3vop_r(light->vect, hit.pos, '-');

		// dclae shadow ray
		t_ray  sdw_ray;
		double bias = 0.0001;
		sdw_ray.org = ft_vec3vop_r(hit.pos, ft_vec3sop_r(hit.nrml, bias,'*'), '+');
		sdw_ray.dir = light_dir;
		ft_vec3normalize(&sdw_ray.dir);
		t_vec3 tmp;
		tmp = ft_vec3vop_r(hit.pos, light->vect, '-');
		sdw_ray.dist = sqrt(ft_dotproduct(tmp, tmp));
		// launch sdw_ray
		if (ft_trace(&sdw_ray, setup))
			hit.col = mult_scale_col(0., hit.col);
	}
	return (hit.col);
}

void multDirMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
	double a;
	double b;
	double c;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2];

	dst->x = a;
	dst->y = b;
	dst->z = c;
}

void multVecMatrix(t_vec3 src, t_vec3 *dst, double **x) {
	double a;
	double b;
	double c;
	double w;

	a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0] + x[3][0];
	b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1] + x[3][1];
	c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2] + x[3][2];
	w = src.x * x[0][3] + src.y * x[1][3] + src.z * x[2][3] + x[3][3];

	dst->x = a / w;
	dst->y = b / w;
	dst->z = c / w;
}

static void		ft_init_primray(t_setup *setup, t_pix pix, t_ray *ray)
{
	double		scale;
	double		imageAspectRatio;
	double		x;
	double		y;

	scale = tan(DEG2RAD((FOV * 0.5)));
	imageAspectRatio = SCN.width / (double)SCN.height;
	x = (2 * (pix.x + 0.5) / (double)SCN.width - 1) * imageAspectRatio * scale;
	y = (1 - 2 * (pix.y + 0.5) / (double)SCN.height) * scale;
	t_vec3 dir = {x, y, -1};
	ft_vec3normalize(&dir);
	multDirMatrix(&dir, &ray->dir, setup->camToWorld);
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
	multVecMatrix(((t_cam *)cam)->org, &ray.org, setup->camToWorld);
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
