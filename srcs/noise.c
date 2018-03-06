/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/06 17:23:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


static const short grad3[16][3] = {
	{ 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 },
	{ 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 },
	{ 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 },
	{ 1, 1, 0 }, { -1, 1, 0 }, { 0, -1, 1 }, { 0, -1, -1 },
};

float gradientDotV(
		uint8_t perm, // a value between 0 and 255
		float x, float y, float z)
{
	uint8_t i;

	i = perm & 15;
	return (x * grad3[i][0] + y * grad3[i][1] + z * grad3[i][2]);
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
	//printf("ft_floor (x) %d\n", ft_floor(x));
	float		gr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	float		k[8];
	float		uvw[3];
	int		xyz0[3];
	int		xyz1[3];

	xyz0[0] = ft_floor(x) & p.tablesizemask;
	xyz0[1] = ft_floor(y) & p.tablesizemask;
	xyz0[2] = ft_floor(z) & p.tablesizemask;

	xyz1[0] = (xyz0[0] + 1) & p.tablesizemask;
	xyz1[1] = (xyz0[1] + 1) & p.tablesizemask;
	xyz1[2] = (xyz0[2] + 1) & p.tablesizemask;

	float tx = x - ft_floor(x);
	float ty = y - ft_floor(y);
	float tz = z - ft_floor(z);

	uvw[0] = ft_quintic(tx);
	uvw[1] = ft_quintic(ty);
	uvw[2] = ft_quintic(tz);

	//gr[0] = gradientDotV(hashtab(p, xyz0[0], xyz0[1], xyz0[2]), tx, ty, tz);
	//gr[1] = gradientDotV(hashtab(p, xyz1[0], xyz0[1], xyz0[2]), tx - 1, ty, tz);
	//gr[2] = gradientDotV(hashtab(p, xyz0[0], xyz1[1], xyz0[2]), tx, ty - 1, tz);
	//gr[3] = gradientDotV(hashtab(p, xyz1[0], xyz1[1], xyz0[2]), tx - 1, ty - 1, tz);
	//gr[4] = gradientDotV(hashtab(p, xyz0[0], xyz0[1], xyz1[2]), tx, ty, tz - 1);
	//gr[5] = gradientDotV(hashtab(p, xyz1[0], xyz0[1], xyz1[2]), tx - 1, ty, tz - 1);
	//gr[6] = gradientDotV(hashtab(p, xyz0[0], xyz1[1], xyz1[2]), tx, ty - 1, tz - 1);
	//gr[7] = gradientDotV(hashtab(p, xyz1[0], xyz1[1], xyz1[2]), tx - 1, ty - 1, tz - 1);

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
