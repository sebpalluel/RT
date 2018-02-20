/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 18:33:57 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

static inline t_ray	calculate_ray(int32_t x, int32_t y, t_setup *setup)
{
	t_ray			ray;
	t_cam			*cam;

	//TODO will be hable to handle which cam is it
	cam = CAM(SCN.cams);
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
//t_bool ft_trace(t_ray *ray,t_setup *setup, t_forms *form)
//{
//	size_t		i; // correspond au type d'objet (par example SPH = 0 et PLN = 1), on tombera donc dans les fonctions d'intersections correspondantes
//	double		dist;
//	t_bool		hit_once;
//	double		t_near;
//	double		t;
//	t_list		*list;
//
//	i = 0;
//	t = MAX_INT;
//	t_near = MAX_INT;
//	hit_once = FALSE;
//	dist = 0;
//	list = SCN.forms;
//	while (list) // ce qui permet de savoir quel est l'objet rencontre et sa fonction d'intersection
//	{
//		ray->hit = FALSE; // je part du principe que ca n'a pas hit
//		if (FORM(list)->type < 2)
//		{
//			ray->hit = param()[FORM(list)->type](ray, FORM(list), &t);
//			if (ray->hit == TRUE && t < t_near)
//			{
//				hit_once = ray->hit;
//				//ray->objn = SPH_N; // permet de savoir l'index de la forme
//				t_near = t;
//				ray->dist = t;
//				//ray->obj = i;
//				*form = *FORM(list);
//				//printf("form trace %p\n", &form);
//			}
//		}
//		list = list->next;
//	}
//	return (hit_once);
//}
//
//
//t_col ft_cast_ray(int i, int j, t_ray ray, t_setup *setup)
//{
//	// double shade;
//	t_col hit_col;
//	t_forms form;
//
//	hit_col = setup->background;
//	i = 0;
//	j = 0;
//	if (ft_trace(&ray, setup, &form))
//	{
//		// t_vec3 hit_point = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
//		// t_vec3 hit_nrml = ft_vec3vop_r(hit_point, OBJDEF.sphere[ray.objn].pos, '-'); // pas besoin pour l instant ?
//		// ft_vec3normalize(&hit_nrml); //add COMMENT 1 under
//		//printf("form after %p\n", &form);
//		if (form.type == SPH)
//			hit_col = form.sph.mat.col;
//		// else if (form.type == PLN)
//		// 	hit_col = form.plan.mat.col;
//		else
//		{
//			hit_col.r = 1.;
//			hit_col.g = 0.;
//			hit_col.b = 0.;
//			hit_col.s = 1.;
//		}
//	}
//	return (hit_col);
//}
//
//void multDirMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
//	double a;
//	double b;
//	double c;
//
//	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0];
//	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1];
//	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2];
//
//	dst->x = a;
//	dst->y = b;
//	dst->z = c;
//}
//
//void multVecMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
//	double a;
//	double b;
//	double c;
//	double w;
//
//	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0] + x[3][0];
//	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1] + x[3][1];
//	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2] + x[3][2];
//	w = src->x * x[0][3] + src->y * x[1][3] + src->z * x[2][3] + x[3][3];
//
//	dst->x = a / w;
//	dst->y = b / w;
//	dst->z = c / w;
//>>>>>>> debug
//}

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
	pthread_mutex_lock(&setup->mutex.mutex);
	while (++pix.y <= (int)(inc * (i + 1) - 1))
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
		{
			ft_put_pixel(setup, pix.x, pix.y, \
					coltoi(send_ray(calculate_ray(pix.x, pix.y, setup), setup)));
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
