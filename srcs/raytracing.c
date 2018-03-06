/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/06 16:50:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

typedef struct	s_perlin2
{
	t_vec3	integer;
	t_vec3	fract;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;
	double		v;
	double		w;
}				t_perlin2;

# define PERSISTANCE	0.7
# define FREQUENCY		0.1
# define OCTAVES		3

//static double	ft_rand2(int x)
//{
//	double		tmp;
//
//	x = (x << 13) ^ x;
//	x = (x * (x * x * 15731 + 789221) + 1376312589);
//	tmp = 1.0 - (x & 0x7fffffff) / 1073741824.0;
//	return (tmp);
//}
//
//double			noise_3d(double x, double y, double z)
//{
//	t_vec3	tmp;
//
//	tmp.x = ft_rand2(x) * 850000;
//	tmp.y = ft_rand2(tmp.x + y) * 850000;
//	return (ft_rand2(tmp.y + z));
//}
//
//double			cos_interpolate(double a, double b, double t)
//{
//	double		c;
//
//	c = (1 - cos(t * 3.1415927)) * 0.5;
//	return ((1 - c) * a + c * b);
//}
//static void		s_n_integer(t_perlin2 *p, double x, double y, double z)
//{
//	if (x >= 0)
//		p->integer.x = (int)x;
//	else
//		p->integer.x = (int)x - 1;
//	if (y >= 0)
//		p->integer.y = (int)y;
//	else
//		p->integer.y = (int)y - 1;
//	if (z >= 0)
//		p->integer.z = (int)z;
//	else
//		p->integer.z = (int)z - 1;
//}
//
//static double	smooth_noise(double x, double y, double z)
//{
//	t_perlin2	p;
//
//	s_n_integer(&p, x, y, z);
//	p.fract.x = x - p.integer.x;
//	p.fract.y = y - p.integer.y;
//	p.fract.z = z - p.integer.z;
//	p.a.y = noise_3d(p.integer.x, p.integer.y, p.integer.z);
//	p.a.z = noise_3d(p.integer.x + 1, p.integer.y, p.integer.z);
//	p.b.y = noise_3d(p.integer.x, p.integer.y + 1, p.integer.z);
//	p.b.z = noise_3d(p.integer.x + 1, p.integer.y + 1, p.integer.z);
//	p.c.y = noise_3d(p.integer.x, p.integer.y, p.integer.z + 1);
//	p.c.z = noise_3d(p.integer.x + 1, p.integer.y, p.integer.z + 1);
//	p.d.y = noise_3d(p.integer.x, p.integer.y + 1, p.integer.z + 1);
//	p.d.z = noise_3d(p.integer.x + 1, p.integer.y + 1, p.integer.z + 1);
//	p.a.x = cos_interpolate(p.a.y, p.a.z, p.fract.x);
//	p.b.x = cos_interpolate(p.b.y, p.b.z, p.fract.x);
//	p.c.x = cos_interpolate(p.c.y, p.c.z, p.fract.x);
//	p.d.x = cos_interpolate(p.d.y, p.d.z, p.fract.x);
//	p.v = cos_interpolate(p.a.x, p.b.x, p.fract.y);
//	p.w = cos_interpolate(p.c.x, p.d.x, p.fract.y);
//	return (cos_interpolate(p.v, p.w, p.fract.z));
//}

double			ft_perlin(t_perlin p, double x, double y, double z)
{
	double		result;
	double		f;
	double		amplitude;
	int			i;
	int			t;

	result = 0;
	f = FREQUENCY;
	amplitude = 1;
	i = -1;
	while (++i < OCTAVES)
	{
		t = i * 4096;
		//result += smooth_noise(x * f + t, y * f + t, z * f + t) * amplitude;
		result += ft_perlin_noise(p, x * f + t, y * f + t, z * f + t) * amplitude;
		amplitude *= PERSISTANCE;
		f *= 2;
	}
	result *= (1 - PERSISTANCE) / (1 - amplitude);
	return (result);
}
//static inline t_ray	calculate_ray(int32_t x, int32_t y, t_setup *setup)
//{
//	t_ray			ray;
//	t_cam			cam;
//	t_vec3			org;
//	t_vec3			dir;
//
//	cam = *SCN.cur_cam;
//	org = ft_vec3vop_r( ft_vec3vop_r(ft_vec3sop_r(cam.rgt, \
//					(x - (SCN.width/ 2.0)) / SCN.height, '*'), \
//				ft_vec3sop_r(cam.dwn, (y - (SCN.height / 2.0)) \
//					/ SCN.height, '*'), '+'), cam.org, '+');
//	dir = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3sop_r(cam.frt, SCN.pers, '*')\
//				, ft_vec3vop_r(cam.org, ft_vec3vop_r(ft_vec3vop_r(\
//							ft_vec3sop_r(cam.rgt, (x - (SCN.width / 2.0)) \
//								/ SCN.height, '*'), \
//							ft_vec3sop_r(cam.dwn, (y - SCN.height / 2.0) \
//								/ SCN.height, '*'), '+'), cam.org, '+'), '-'),\
//				'-'));
//	ray = init_ray(org, dir);
//	return (ray);
//}

void			*ft_raytracing(void *a)
{
	t_setup		*setup;
	t_pix		pix;
	pthread_t	id;
	size_t		thread_n;
	size_t		inc;
	float		perlin;

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
			//perlin = ft_perlin_noise(setup->p, (double)pix.x + 0.1, (double)pix.y + 0.1, (double)pix.z + 0.1);
			perlin = ft_perlin(setup->p, (double)pix.x, (double)pix.y, (double)pix.z);
			ft_put_pixel(setup, pix.x, pix.y, ft_coltoi(ft_col_r(perlin, perlin, perlin, 1.)));
			//ft_put_pixel(setup, pix.x, pix.y, \
			//		ft_coltoi(send_ray(calculate_ray(pix.x, pix.y, setup), \
			//				setup)));
		}
	}
	//pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
