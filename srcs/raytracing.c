/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/06 19:49:27 by psebasti         ###   ########.fr       */
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
# define OCTAVES		5

#define FASTFLOOR(x) ( ((int)(x)<(x)) ? ((int)x) : ((int)x-1 ) )
#define LERP(t, a, b) ((a) + (t)*((b)-(a)))


unsigned char perm[] = {151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
  151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

float grad3( int hash, float x, float y , float z ) {
    int h = hash & 15;     // Convert low 4 bits of hash code into 12 simple
    float u = h<8 ? x : y; // gradient directions, and compute dot product.
    float v = h<4 ? y : h==12||h==14 ? x : z; // Fix repeats at h = 12 to 15
    return ((h&1)? -u : u) + ((h&2)? -v : v);
}

float noise3(float x, float y, float z )
{
    int ix0, iy0, ix1, iy1, iz0, iz1;
    float fx0, fy0, fz0, fx1, fy1, fz1;
    float s, t, r;
    float nxy0, nxy1, nx0, nx1, n0, n1;

    ix0 = FASTFLOOR( x ); // Integer part of x
    iy0 = FASTFLOOR( y ); // Integer part of y
    iz0 = FASTFLOOR( z ); // Integer part of z
    fx0 = x - ix0;        // Fractional part of x
    fy0 = y - iy0;        // Fractional part of y
    fz0 = z - iz0;        // Fractional part of z
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    fz1 = fz0 - 1.0f;
    ix1 = ( ix0 + 1 ) & P_TABLESIZE; // Wrap to 0..255
    iy1 = ( iy0 + 1 ) & P_TABLESIZE;
    iz1 = ( iz0 + 1 ) & P_TABLESIZE;
    ix0 = ix0 & P_TABLESIZE;
    iy0 = iy0 & P_TABLESIZE;
    iz0 = iz0 & P_TABLESIZE;
    
    r = ft_quintic( fz0 );
    t = ft_quintic( fy0 );
    s = ft_quintic( fx0 );

    nxy0 = grad3(perm[ix0 + perm[iy0 + perm[iz0]]], fx0, fy0, fz0);
    nxy1 = grad3(perm[ix0 + perm[iy0 + perm[iz1]]], fx0, fy0, fz1);
    nx0 = LERP( r, nxy0, nxy1 );

    nxy0 = grad3(perm[ix0 + perm[iy1 + perm[iz0]]], fx0, fy1, fz0);
    nxy1 = grad3(perm[ix0 + perm[iy1 + perm[iz1]]], fx0, fy1, fz1);
    nx1 = LERP( r, nxy0, nxy1 );

    n0 = LERP( t, nx0, nx1 );

    nxy0 = grad3(perm[ix1 + perm[iy0 + perm[iz0]]], fx1, fy0, fz0);
    nxy1 = grad3(perm[ix1 + perm[iy0 + perm[iz1]]], fx1, fy0, fz1);
    nx0 = LERP( r, nxy0, nxy1 );

    nxy0 = grad3(perm[ix1 + perm[iy1 + perm[iz0]]], fx1, fy1, fz0);
    nxy1 = grad3(perm[ix1 + perm[iy1 + perm[iz1]]], fx1, fy1, fz1);
    nx1 = LERP( r, nxy0, nxy1 );

    n1 = LERP( t, nx0, nx1 );
    
    return 0.936f * ( LERP( s, n0, n1 ) );
}


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

double			ft_perlin(double x, double y, double z)
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
		result += noise3(x * f + t, y * f + t, z * f + t) * amplitude;
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
			perlin = ft_perlin((double)pix.x, (double)pix.y, (double)pix.z);
			ft_put_pixel(setup, pix.x, pix.y, ft_coltoi(ft_col_r(perlin, perlin, perlin, 1.)));
			//ft_put_pixel(setup, pix.x, pix.y, \
			//		ft_coltoi(send_ray(calculate_ray(pix.x, pix.y, setup), \
			//				setup)));
		}
	}
	//pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
