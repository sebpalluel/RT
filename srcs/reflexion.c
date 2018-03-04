/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/02/26 15:42:26 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_ray		reflexion(t_ray ray, t_vec3 norm)
{
	t_ray	newray;
	double	reflect;

	reflect = 2 * ft_dotproduct(norm, ray.dir);
	newray.org = ft_vec3vop_r(ft_vec3sop_r(ray.dir, (ray.dist - 0.00000001), '*'), ray.org, '+');
	newray.dir = ft_vec3normalize_r(ft_vec3vop_r(ray.dir, ft_vec3sop_r(norm, reflect, '*'), '-'));
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl + 1;
	newray.n = ray.n;
	return (newray);
}

/*
**  n1 sin(i1) = n2 sin(i2);
*/

t_ray		refraction(t_ray ray, t_vec3 norm, double n2)
{
	t_ray	newray;
	t_vec3	dir;
	double	cosi1;
	double	sini1;
	double	sini2;
	double	cosi2;

	cosi1 = ft_dotproduct(norm, ray.dir);
	sini1 = sqrt(1 - cosi1 * cosi1);
	sini2 = ray.n * (((double)sini1) / n2);
	if (sini2 > 1)
	{
		newray.dir = ft_vec3_r(0,0,0);
		return (newray);
	}
	newray.org = ft_vec3vop_r(ft_vec3sop_r(ray.dir, (ray.dist + 0.000001), '*'), ray.org, '+');
	newray.n = n2;
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl;

	cosi2 = sqrt(1 - sini2 * sini2);

//	newray.dir = ft_vec3vop_r(ft_vec3sop_r(ray.dir, (ray.n / (double)n2), '*'), ft_vec3sop_r(ray.dir, ((ray.n / (double)n2) * cosi1) - cosi2, '*'),'+');
//	newray.dir = ft_vec3normalize_r(ft_vec3sop_r(newray.dir, -1, '*'));
	dir = ft_vec3normalize_r(ft_vec3vop_r(ray.dir, ft_vec3sop_r(norm, ft_dotproduct(ray.dir, norm), '*'), '-'));
	newray.dir = ft_vec3vop_r(ft_vec3sop_r(norm, -cosi2,'*'), ft_vec3sop_r(dir, sini2,'*'), '+');
//	printf("%f, %f, %f, %f, %f, %f, %f\n", dir.x, dir.y, dir.z, norm.x, norm.y, norm.z, ft_dotproduct(norm, dir));
	return (newray);
}