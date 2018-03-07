/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/07 12:09:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

unsigned char	perm2[512] = {217, \
	150, 31, 204, 241, 104, 201, 34, 39, 210, 177, 232, 160, 162, 128, 102, \
	2, 26, 95, 134, 108, 194, 143, 230, 216, 228, 82, 212, 168, 118, 67, \
	48, 213, 236, 158, 142, 225, 2, 133, 156, 29, 72, 231, 41, 235, 15, \
	49, 178, 12, 5, 27, 180, 195, 44, 60, 9, 138, 130, 197, 198, 21, \
	8, 152, 252, 114, 172, 46, 54, 101, 220, 8, 90, 48, 65, 206, 1, \
	18, 59, 191, 240, 139, 30, 205, 77, 233, 33, 32, 6, 215, 38, 10, \
	5, 199, 53, 73, 28, 196, 51, 221, 246, 69, 58, 187, 200, 87, 242, \
	6, 202, 94, 136, 253, 234, 237, 226, 3, 250, 92, 11, 219, 85, 22, \
	13, 151, 24, 159, 88, 243, 125, 207, 61, 126, 13, 227, 80, 175, 70, \
	0, 132, 20, 64, 186, 224, 17, 244, 120, 68, 7, 75, 81, 89, 181, \
	6, 161, 91, 40, 49, 211, 155, 249, 164, 79, 166, 179, 248, 131, 214, \
	05, 57, 222, 122, 174, 135, 176, 115, 74, 19, 25, 173, 251, 154, 93, \
	54, 203, 63, 43, 71, 18, 106, 55, 190, 141, 165, 245, 119, 123, 103, \
	3, 47, 37, 184, 76, 52, 185, 112, 107, 145, 84, 116, 147, 183, 209, \
	00, 223, 121, 189, 169, 208, 45, 14, 36, 0, 146, 127, 97, 66, 157, \
	47, 193, 144, 167, 238, 171, 239, 4, 96, 99, 137, 117, 170, 182, 109, \
	11, 140, 78, 229, 124, 129, 188, 42, 153, 23, 110, 192, 163, 16, 217, \
	50, 31, 204, 241, 104, 201, 34, 39, 210, 177, 232, 160, 162, 128, 102, \
	2, 26, 95, 134, 108, 194, 143, 230, 216, 228, 82, 212, 168, 118, 67, \
	48, 213, 236, 158, 142, 225, 2, 133, 156, 29, 72, 231, 41, 235, 15, \
	49, 178, 12, 5, 27, 180, 195, 44, 60, 9, 138, 130, 197, 198, 21, \
	8, 152, 252, 114, 172, 46, 54, 101, 220, 8, 90, 48, 65, 206, 1, \
	18, 59, 191, 240, 139, 30, 205, 77, 233, 33, 32, 6, 215, 38, 10, \
	5, 199, 53, 73, 28, 196, 51, 221, 246, 69, 58, 187, 200, 87, 242, \
	6, 202, 94, 136, 253, 234, 237, 226, 3, 250, 92, 11, 219, 85, 22, \
	13, 151, 24, 159, 88, 243, 125, 207, 61, 126, 13, 227, 80, 175, 70, \
	0, 132, 20, 64, 186, 224, 17, 244, 120, 68, 7, 75, 81, 89, 181, \
	6, 161, 91, 40, 49, 211, 155, 249, 164, 79, 166, 179, 248, 131, 214, \
	05, 57, 222, 122, 174, 135, 176, 115, 74, 19, 25, 173, 251, 154, 93, \
	54, 203, 63, 43, 71, 18, 106, 55, 190, 141, 165, 245, 119, 123, 103, \
	3, 47, 37, 184, 76, 52, 185, 112, 107, 145, 84, 116, 147, 183, 209, \
	00, 223, 121, 189, 169, 208, 45, 14, 36, 0, 146, 127, 97, 66, 157, \
	47, 193, 144, 167, 238, 171, 239, 4, 96, 99, 137, 117, 170, 182, 109};


//static double	ft_rand2(int x)
//{
//	double		tmp;
//
//	x = (x << 13) ^ x;
//	x = (x * (x * x * 15731 + 789221) + 1376312589);
//	tmp = 1.0 - (x & 0x7fffffff) / 1073741824.0;
//	return (tmp);
//}

float ft_grad3( int hash, float x, float y , float z ) {
    int h = hash & 15;     // Convert low 4 bits of hash code into 12 simple
    float u = h<8 ? x : y; // gradient directions, and compute dot product.
    float v = h<4 ? y : h==12||h==14 ? x : z; // Fix repeats at h = 12 to 15
    return ((h&1)? -u : u) + ((h&2)? -v : v);
}

static const short gradtab[16][3] = {
	{ 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 },
	{ 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 },
	{ 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 },
	{ 1, 1, 0 }, { -1, 1, 0 }, { 0, -1, 1 }, { 0, -1, -1 },
};

float gradientDotV(
		uint8_t perm2, // a value between 0 and 255
		float x, float y, float z)
{
	uint8_t i;

	i = perm2 & 15;
	return (x * gradtab[i][0] + y * gradtab[i][1] + z * gradtab[i][2]);
}


uint8_t		hashtab(const int x, const int y, const int z)
{
    return (perm2[perm2[perm2[x] + y] + z]);
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

static float	dotprodfrom4unitcube_0(int ixyz0[3], int ixyz1[3], float fxyz[3], float uvw[3])
{
	float		nxy0;
	float 		nxy1;
	float		nx0;
	float		nx1;

	nxy0 = gradientDotV(hashtab(ixyz0[0], ixyz0[1], ixyz0[2]), fxyz[0], fxyz[1], fxyz[2]);
	nxy1 = gradientDotV(hashtab(ixyz1[0], ixyz0[1], ixyz0[2]), fxyz[0] - 1, fxyz[1], fxyz[2]);
	nx0 = ft_lerp(uvw[0], nxy0, nxy1);
	nxy0 = gradientDotV(hashtab(ixyz0[0], ixyz1[1], ixyz0[2]), fxyz[0], fxyz[1] - 1, fxyz[2]);
	nxy1 = gradientDotV(hashtab(ixyz1[0], ixyz1[1], ixyz0[2]), fxyz[0] - 1, fxyz[1] - 1, fxyz[2]);
	nx1 = ft_lerp(uvw[0], nxy0, nxy1);
	return (ft_lerp(uvw[1], nx0, nx1));
}

static float	dotprodfrom4unitcube_1(int ixyz0[3], int ixyz1[3], float fxyz[3], float uvw[3])
{
	float		nxy0;
	float 		nxy1;
	float		nx0;
	float		nx1;

	nxy0 = gradientDotV(hashtab(ixyz0[0], ixyz0[1], ixyz1[2]), fxyz[0], fxyz[1], fxyz[2] - 1);
	nxy1 = gradientDotV(hashtab(ixyz1[0], ixyz0[1], ixyz1[2]), fxyz[0] - 1, fxyz[1], fxyz[2] - 1);
	nx0 = ft_lerp(uvw[0], nxy0, nxy1);
	nxy0 = gradientDotV(hashtab(ixyz0[0], ixyz1[1], ixyz1[2]), fxyz[0], fxyz[1] - 1, fxyz[2] - 1);
	nxy1 = gradientDotV(hashtab(ixyz1[0], ixyz1[1], ixyz1[2]), fxyz[0] - 1, fxyz[1] - 1, fxyz[2] - 1);
	nx1 = ft_lerp(uvw[0], nxy0, nxy1);
	return (ft_lerp(uvw[1], nx0, nx1));
}

float			ft_perlin_noise(double x, double y, double z)
{
	float		uvw[3];
	int			ixyz0[3];
	int			ixyz1[3];
	float		fxyz[3];
	float		n[2];


	ixyz0[0] = ft_floor(x) & 0xff;
	ixyz0[1] = ft_floor(y) & 0xff;
	ixyz0[2] = ft_floor(z) & 0xff;

	ixyz1[0] = (ixyz0[0] + 1) & 0xff;
	ixyz1[1] = (ixyz0[1] + 1) & 0xff;
	ixyz1[2] = (ixyz0[2] + 1) & 0xff;

	fxyz[0] = x - ft_floor(x);
	fxyz[1] = y - ft_floor(y);
	fxyz[2] = z - ft_floor(z);

	uvw[0] = ft_quintic(fxyz[0]);
	uvw[1] = ft_quintic(fxyz[1]);
	uvw[2] = ft_quintic(fxyz[2]);

	n[0] = dotprodfrom4unitcube_0(ixyz0, ixyz1, fxyz, uvw);
	n[1] = dotprodfrom4unitcube_1(ixyz0, ixyz1, fxyz, uvw);
	return (ft_lerp(uvw[2], n[0], n[1]) * 0.98);
	//return ((ft_lerp(uvw[2], n[0], n[1]) + 1) / 2); this one is a lot smoother
}
