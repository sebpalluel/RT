/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/05 18:29:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


//static const char grad3[][3] = {
//	{ 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 },
//	{ 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 },
//	{ 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 }
//};

//float gradientDotV(
//		uint8_t perm, // a value between 0 and 255
//		float x, float y, float z) const
//{
//	switch (perm & 15) {
//		case  0: return  x + y; // (1,1,0)
//		case  1: return -x + y; // (-1,1,0)
//		case  2: return  x - y; // (1,-1,0)
//		case  3: return -x - y; // (-1,-1,0)
//		case  4: return  x + z; // (1,0,1)
//		case  5: return -x + z; // (-1,0,1)
//		case  6: return  x - z; // (1,0,-1)
//		case  7: return -x - z; // (-1,0,-1)
//		case  8: return  y + z; // (0,1,1),
//		case  9: return -y + z; // (0,-1,1),
//		case 10: return  y - z; // (0,1,-1),
//		case 11: return -y - z; // (0,-1,-1)
//		case 12: return  y + x; // (1,1,0)
//		case 13: return -x + y; // (-1,1,0)
//		case 14: return -y + z; // (0,-1,1)
//		case 15: return -y - z; // (0,-1,-1)
//	}
//}

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

t_perlin		ft_perlin_init(uint32_t seed)
{
	t_perlin	p;
	int			i;

	srand(seed);
	p.tablesizemask = P_TABLESIZE - 1;
	ft_perlin_init_grad(&p);
	// create permutation table
	i = -1;
	while (++i < P_TABLESIZE)
		ft_swap((void *)&p.permtable[i], \
				(void *)&p.permtable[ft_rand() & p.tablesizemask], \
				sizeof(uint32_t));
	// extend the permutation table in the index range [256:512]
	i = -1;
	while (++i < P_TABLESIZE)
		p.permtable[P_TABLESIZE + i] = p.permtable[i];
	return (p);
}

//float eval(const Vec3f &p, Vec3f& derivs) const 
//{
//	int xi0 = ((int)std::floor(p.x)) & tableSizeMask;
//	int yi0 = ((int)std::floor(p.y)) & tableSizeMask;
//	int zi0 = ((int)std::floor(p.z)) & tableSizeMask;
//
//	int xi1 = (xi0 + 1) & tableSizeMask;
//	int yi1 = (yi0 + 1) & tableSizeMask;
//	int zi1 = (zi0 + 1) & tableSizeMask;
//
//	float tx = p.x - ((int)std::floor(p.x));
//	float ty = p.y - ((int)std::floor(p.y));
//	float tz = p.z - ((int)std::floor(p.z));
//
//	float u = quintic(tx);
//	float v = quintic(ty);
//	float w = quintic(tz);
//
//	// generate vectors going from the grid points to p
//	float x0 = tx, x1 = tx - 1;
//	float y0 = ty, y1 = ty - 1;
//	float z0 = tz, z1 = tz - 1;
//
//	float a = gradientDotV(hash(xi0, yi0, zi0), x0, y0, z0);
//	float b = gradientDotV(hash(xi1, yi0, zi0), x1, y0, z0);
//	float c = gradientDotV(hash(xi0, yi1, zi0), x0, y1, z0);
//	float d = gradientDotV(hash(xi1, yi1, zi0), x1, y1, z0);
//	float e = gradientDotV(hash(xi0, yi0, zi1), x0, y0, z1);
//	float f = gradientDotV(hash(xi1, yi0, zi1), x1, y0, z1);
//	float g = gradientDotV(hash(xi0, yi1, zi1), x0, y1, z1);
//	float h = gradientDotV(hash(xi1, yi1, zi1), x1, y1, z1);
//
//	float du = quinticDeriv(tx);
//	float dv = quinticDeriv(ty);
//	float dw = quinticDeriv(tz);
//
//	float k0 = a;
//	float k1 = (b - a);
//	float k2 = (c - a);
//	float k3 = (e - a);
//	float k4 = (a + d - b - c);
//	float k5 = (a + f - b - e);
//	float k6 = (a + g - c - e);
//	float k7 = (b + c + e + h - a - d - f - g);
//
//	derivs.x = du *(k1 + k4 * v + k5 * w + k7 * v * w);
//	derivs.y = dv *(k2 + k4 * u + k6 * w + k7 * v * w);
//	derivs.z = dw *(k3 + k5 * u + k6 * v + k7 * v * w);
//
//	return k0 + k1 * u + k2 * v + k3 * w + k4 * u * v + k5 * u * w + k6 * v * w + k7 * u * v * w;
//}
