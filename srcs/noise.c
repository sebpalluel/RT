/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/06 19:51:32 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

unsigned char perm2[] = {151,160,137,91,90,15,
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

float			ft_perlin_noise(double x, double y, double z)
{
	//printf("ft_floor (x) %d\n", ft_floor(x));
	float		gr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	float		k[8];
	float		uvw[3];
	int			xyz0[3];
	int			xyz1[3];
	float		txyz[3];

	xyz0[0] = ft_floor(x) & 0xff;
	xyz0[1] = ft_floor(y) & 0xff;
	xyz0[2] = ft_floor(z) & 0xff;

	xyz1[0] = (xyz0[0] + 1) & 0xff;
	xyz1[1] = (xyz0[1] + 1) & 0xff;
	xyz1[2] = (xyz0[2] + 1) & 0xff;

	txyz[0] = x - ft_floor(x);
	txyz[1] = y - ft_floor(y);
	txyz[2] = z - ft_floor(z);

	uvw[0] = ft_quintic(txyz[0]);
	uvw[1] = ft_quintic(txyz[1]);
	uvw[2] = ft_quintic(txyz[2]);

	gr[0] = gradientDotV(hashtab(xyz0[0], xyz0[1], xyz0[2]), txyz[0], txyz[1], txyz[2]);
	gr[1] = gradientDotV(hashtab(xyz1[0], xyz0[1], xyz0[2]), txyz[0] - 1, txyz[1], txyz[2]);
	gr[2] = gradientDotV(hashtab(xyz0[0], xyz1[1], xyz0[2]), txyz[0], txyz[1] - 1, txyz[2]);
	gr[3] = gradientDotV(hashtab(xyz1[0], xyz1[1], xyz0[2]), txyz[0] - 1, txyz[1] - 1, txyz[2]);
	gr[4] = gradientDotV(hashtab(xyz0[0], xyz0[1], xyz1[2]), txyz[0], txyz[1], txyz[2] - 1);
	gr[5] = gradientDotV(hashtab(xyz1[0], xyz0[1], xyz1[2]), txyz[0] - 1, txyz[1], txyz[2] - 1);
	gr[6] = gradientDotV(hashtab(xyz0[0], xyz1[1], xyz1[2]), txyz[0], txyz[1] - 1, txyz[2] - 1);
	gr[7] = gradientDotV(hashtab(xyz1[0], xyz1[1], xyz1[2]), txyz[0] - 1, txyz[1] - 1, txyz[2] - 1);

	//gr[0] = ft_grad3(, txyz[0], txyz[1], txyz[2]);
	//gr[1] = ft_grad3(, txyz[0] - 1, txyz[1], txyz[2]);
	//gr[2] = ft_grad3(, txyz[0], txyz[1] - 1, txyz[2]);
	//gr[3] = ft_grad3(, txyz[0] - 1, txyz[1] - 1, txyz[2]);
	//gr[4] = ft_grad3(, txyz[0], txyz[1], txyz[2] - 1);
	//gr[5] = ft_grad3(, txyz[0] - 1, txyz[1], txyz[2] - 1);
	//gr[6] = ft_grad3(, txyz[0], txyz[1] - 1, txyz[2] - 1);
	//gr[7] = ft_grad3(, txyz[0] - 1, txyz[1] - 1, txyz[2] - 1);
	
	k[0] = gr[0];
	k[1] = (gr[1] - gr[0]);
	k[2] = (gr[2] - gr[0]);
	k[3] = (gr[4] - gr[0]);
	k[4] = (gr[0] + gr[3] - gr[1] - gr[2]);
	k[5] = (gr[0] + gr[5] - gr[1] - gr[4]);
	k[6] = (gr[0] + gr[6] - gr[2] - gr[4]);
	k[7] = (gr[1] + gr[2] + gr[4] + gr[7] - gr[0] - gr[3] - gr[5] - gr[6]);

	return k[0] + k[1] * uvw[0] + k[2] * uvw[1] + k[3] * uvw[2] + k[4] * uvw[0] * uvw[1] + k[5] * uvw[0] * uvw[2] + k[6] * uvw[1] * uvw[2] + k[7] * uvw[0] * uvw[1] * uvw[2];
}
