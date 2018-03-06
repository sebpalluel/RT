/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/06 14:34:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


//static const char grad3[][3] = {
//	{ 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 },
//	{ 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 },
//	{ 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 }
//};

float gradientDotV(
		uint8_t perm, // a value between 0 and 255
		float x, float y, float z)
{
	switch (perm & 15) {
		case  0: return  x + y; // (1,1,0)
		case  1: return -x + y; // (-1,1,0)
		case  2: return  x - y; // (1,-1,0)
		case  3: return -x - y; // (-1,-1,0)
		case  4: return  x + z; // (1,0,1)
		case  5: return -x + z; // (-1,0,1)
		case  6: return  x - z; // (1,0,-1)
		case  7: return -x - z; // (-1,0,-1)
		case  8: return  y + z; // (0,1,1),
		case  9: return -y + z; // (0,-1,1),
		case 10: return  y - z; // (0,1,-1),
		case 11: return -y - z; // (0,-1,-1)
		case 12: return  y + x; // (1,1,0)
		case 13: return -x + y; // (-1,1,0)
		case 14: return -y + z; // (0,-1,1)
		case 15: return -y - z; // (0,-1,-1)
	}
	return (0);
}

uint8_t		hashtab(t_perlin p, const int x, const int y, const int z)
{
    return (p.permtable[p.permtable[p.permtable[x] + y] + z]);
}

void			ft_perlin_init_grad(t_perlin *p)
{
	int			i;
	float		theta;
	float		phi;

	i = -1;
	while (++i < P_TABLESIZE) 
	{
		theta = acos(2 * ft_randf() - 1);
		phi = 2 * ft_randf() * M_PI;
		p->gradient[i] = ft_vec3_r(cos(phi) * sin(theta), \
				sin(phi) * sin(theta), cos(theta));
		p->permtable[i] = i;
	}
}

void		ft_perlin_init(t_perlin *p, uint32_t seed)
{
	int			i;

	srand(seed);
	p->tablesizemask = P_TABLESIZE - 1;
	ft_perlin_init_grad(p);
	// create permutation table
	i = -1;
	while (++i < P_TABLESIZE)
		ft_swap((void *)&p->permtable[i], \
				(void *)&p->permtable[ft_rand() & p->tablesizemask], \
				sizeof(uint32_t));
	// extend the permutation table in the index range [256:512]
	i = -1;
	while (++i < P_TABLESIZE)
		p->permtable[P_TABLESIZE + i] = p->permtable[i];
	p->init = TRUE;
}

float			ft_perlin_noise(t_perlin p, double x, double y, double z)
{
	int xi0 = ((int)floor(x)) & p.tablesizemask;
	int yi0 = ((int)floor(y)) & p.tablesizemask;
	int zi0 = ((int)floor(z)) & p.tablesizemask;

	int xi1 = (xi0 + 1) & p.tablesizemask;
	int yi1 = (yi0 + 1) & p.tablesizemask;
	int zi1 = (zi0 + 1) & p.tablesizemask;

	float tx = x - ((int)floor(x));
	float ty = y - ((int)floor(y));
	float tz = z - ((int)floor(z));

	float u = ft_quintic(tx);
	float v = ft_quintic(ty);
	float w = ft_quintic(tz);

	// generate vectors going from the grid points to p
	float x0 = tx, x1 = tx - 1;
	float y0 = ty, y1 = ty - 1;
	float z0 = tz, z1 = tz - 1;

	float a = gradientDotV(hashtab(p, xi0, yi0, zi0), x0, y0, z0);
	float b = gradientDotV(hashtab(p, xi1, yi0, zi0), x1, y0, z0);
	float c = gradientDotV(hashtab(p, xi0, yi1, zi0), x0, y1, z0);
	float d = gradientDotV(hashtab(p, xi1, yi1, zi0), x1, y1, z0);
	float e = gradientDotV(hashtab(p, xi0, yi0, zi1), x0, y0, z1);
	float f = gradientDotV(hashtab(p, xi1, yi0, zi1), x1, y0, z1);
	float g = gradientDotV(hashtab(p, xi0, yi1, zi1), x0, y1, z1);
	float h = gradientDotV(hashtab(p, xi1, yi1, zi1), x1, y1, z1);

	float k0 = a;
	float k1 = (b - a);
	float k2 = (c - a);
	float k3 = (e - a);
	float k4 = (a + d - b - c);
	float k5 = (a + f - b - e);
	float k6 = (a + g - c - e);
	float k7 = (b + c + e + h - a - d - f - g);

	return k0 + k1 * u + k2 * v + k3 * w + k4 * u * v + k5 * u * w + k6 * v * w + k7 * u * v * w;
}
