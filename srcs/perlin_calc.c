/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:34:05 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 22:09:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline float		getgradformvec(uint8_t perm, t_vec3 vec3)
{
	return (ft_dotproduct(vec3, g_gradtab[perm & 15]));
}

static inline uint8_t	hashtab(const int x, const int y, const int z)
{
	return (g_perm[g_perm[g_perm[x] + y] + z]);
}

static float			dotprodfrom4unitcube_0(int ixyz0[3], int ixyz1[3], \
		t_vec3 frac, float uvw[3])
{
	float				nxy0;
	float				nxy1;
	float				nx0;
	float				nx1;

	nxy0 = getgradformvec(hashtab(ixyz0[0], ixyz0[1], ixyz0[2]), \
			ft_vec3add_r(frac, g_unitcube[0]));
	nxy1 = getgradformvec(hashtab(ixyz1[0], ixyz0[1], ixyz0[2]), \
			ft_vec3add_r(frac, g_unitcube[1]));
	nx0 = ft_lerp(uvw[0], nxy0, nxy1);
	nxy0 = getgradformvec(hashtab(ixyz0[0], ixyz1[1], ixyz0[2]), \
			ft_vec3add_r(frac, g_unitcube[2]));
	nxy1 = getgradformvec(hashtab(ixyz1[0], ixyz1[1], ixyz0[2]), \
			ft_vec3add_r(frac, g_unitcube[3]));
	nx1 = ft_lerp(uvw[0], nxy0, nxy1);
	return (ft_lerp(uvw[1], nx0, nx1));
}

static float			dotprodfrom4unitcube_1(int ixyz0[3], int ixyz1[3], \
		t_vec3 frac, float uvw[3])
{
	float				nxy0;
	float				nxy1;
	float				nx0;
	float				nx1;

	nxy0 = getgradformvec(hashtab(ixyz0[0], ixyz0[1], ixyz1[2]), \
			ft_vec3add_r(frac, g_unitcube[4]));
	nxy1 = getgradformvec(hashtab(ixyz1[0], ixyz0[1], ixyz1[2]), \
			ft_vec3add_r(frac, g_unitcube[5]));
	nx0 = ft_lerp(uvw[0], nxy0, nxy1);
	nxy0 = getgradformvec(hashtab(ixyz0[0], ixyz1[1], ixyz1[2]), \
			ft_vec3add_r(frac, g_unitcube[6]));
	nxy1 = getgradformvec(hashtab(ixyz1[0], ixyz1[1], ixyz1[2]), \
			ft_vec3add_r(frac, g_unitcube[7]));
	nx1 = ft_lerp(uvw[0], nxy0, nxy1);
	return (ft_lerp(uvw[1], nx0, nx1));
}

float					ft_perlin_noise(double x, double y, double z)
{
	float				uvw[3];
	int					ixyz0[3];
	int					ixyz1[3];
	t_vec3				frac;
	float				n[2];

	ixyz0[0] = ft_floor(x) & 0xff;
	ixyz0[1] = ft_floor(y) & 0xff;
	ixyz0[2] = ft_floor(z) & 0xff;
	ixyz1[0] = (ixyz0[0] + 1) & 0xff;
	ixyz1[1] = (ixyz0[1] + 1) & 0xff;
	ixyz1[2] = (ixyz0[2] + 1) & 0xff;
	frac.x = x - ft_floor(x);
	frac.y = y - ft_floor(y);
	frac.z = z - ft_floor(z);
	uvw[0] = ft_quintic(frac.x);
	uvw[1] = ft_quintic(frac.y);
	uvw[2] = ft_quintic(frac.z);
	n[0] = dotprodfrom4unitcube_0(ixyz0, ixyz1, frac, uvw);
	n[1] = dotprodfrom4unitcube_1(ixyz0, ixyz1, frac, uvw);
	return (ft_lerp(uvw[2], n[0], n[1]) * 0.98);
}
