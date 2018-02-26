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

/*
 **	test les intersections rayon | forme
 **	au retour de la fonction on a:
 **		la forme la plus proche rencontrée dans form
 **		la distance a cette cette forme dans ray.dist
 */
t_forms 		*ft_trace(t_ray *ray, t_setup *setup)
{
	// double		dist;
	t_forms		*form;
	double		t_near;
	double		t;
	t_list		*list;

	t = MAX_INT;
	// t = inf;
	t_near = ray->dist == -1 ? MAX_INT : ray->dist;
	form = NULL;
	// dist = 0;
	list = SCN.forms;
	while (list) /* itere sur tous les objets de la scene */
	{
		ray->hit = FALSE;
		if (FORM(list)->type <= 3)
		{
			ray->hit = param()[FORM(list)->type](ray, FORM(list), &t); /* test la routine d intersection correspondant a l objet */
			if ((ray->hit == TRUE && t < t_near))
			{
				// ICI CHECK SI L OBJET RENCONTRE DANS LE SHADOW RAY EST AVANT LA SOURCE DE LUMIERE (t < ray->dist)
				// SAUF QUE CA MARCHE PAS IL TRAVERSE LA LUMIERE
				t_near = t;
				ray->dist = t_near;
				form = FORM(list);
			}
		}
		list = list->next;
	}
	return (form);
}

// static t_bool	ft_trace_shadow(t_ray *ray, t_setup *setup, t_forms *obj)
// {
// 	t_forms		*shadow;
//
// 	shadow = ft_trace(ray, setup);
// 	if (shadow && shadow != obj)
// 		return (TRUE);
// 	return (FALSE);
// }
/*
   void ft_get_surface_data(t_vec3 *hit_point, t_vec3 *hit_nrml, t_vec3 *hit_text)
   {
 *
 **	void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const
 **  {
 ** 			Set surface data such as normal and texture coordinates at a given point on the surface
 ** 			\param Phit is the point ont the surface we want to get data on
 ** 			\param[out] Nhit is the normal at Phit
 ** 			\param[out] tex are the texture coordinates at Phit
 **************
 **      Nhit = Phit - center; () (calcul de la normale au point d'intersection) pour la sphere
 **      Nhit.normalize();  On normalise le vecteur
 **************
 **      In this particular case, the normal is simular to a point on a unit sphere
 **      centred around the origin. We can thus use the normal coordinates to compute
 **      the spherical coordinates of Phit.
 **      atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
 **      acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
 **************
 **      tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5; -> a defini je suis pas mega au clair
 **      tex.y = acosf(Nhit.y) / M_PI;
 **  }
 *
 }

 TODO Notes sur ft_cast_ray

// retourne couleur de l'objet
on doit :
 ** trouver l'objet
 ** set la hit_col a la couleur de l'objet rencontré
 */

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

t_col ft_cast_ray(int i, int j, t_ray ray, t_setup *setup)
{
	t_col hit_col;
	t_forms *form;
	t_lgt *light = LGT(SCN.lgts);
	t_vec3 hit_nrml = {0,0,0};
	hit_col = setup->background;
	i = 0;
	j = 0;
	form = NULL;
	if ((form = ft_trace(&ray, setup)))
	{
		t_vec3 hit_point = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
		hit_nrml = get_nrml()[form->type](ray, form);
		if (form->type == SPH)
		{
			hit_col = form->sph.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->sph.mat, light);
		}
		else if (form->type == PLN)
		{
			hit_col = form->plan.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->plan.mat, light);
			// if (hit_nrml.z < 0)
			//    hit_nrml = ft_vec3sop_r(form->plan.nrml, -1, '*');
		}
		else if (form->type == CON)
		{
			hit_col = form->cone.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->cone.mat, light);
		}
		else if (form->type == CYL)
		{
			hit_col = form->cldre.mat.col;
			// hit_col = illuminate(&hit_point, &hit_nrml, &form->cldre.mat, light);
		}
		else
		{
			hit_col.r = 1.;
			hit_col.g = 0.;
			hit_col.b = 0.;
			hit_col.s = 1.;
		}
		t_vec3 light_dir = ft_vec3vop_r(light->vect, hit_point, '-');
		t_ray  sdw_ray;
		double bias = 0.000001;
		sdw_ray.org = ft_vec3vop_r(hit_point, ft_vec3sop_r(hit_nrml, bias,'*'), '+');
		sdw_ray.dir = light_dir;
		ft_vec3normalize(&sdw_ray.dir);
		sdw_ray.dist = ray.dist;
		// if (ft_trace(&sdw_ray, setup))
		// 	hit_col = mult_scale_col(0., hit_col);
	}
	return (hit_col);
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

// TODO CameraToWorld transfo https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
// TODO Refacto

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
					ft_coltoi(ft_cast_ray(pix.x, pix.y, ray, setup)));
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
