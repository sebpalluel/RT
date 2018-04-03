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
	newray.org = ft_vec3vop_r(ft_vec3sop_r(ray.dir, (ray.dist - 0.00000001),
		'*'), ray.org, '+');
	newray.dir = ft_vec3normalize_r(ft_vec3vop_r(ray.dir, ft_vec3sop_r(norm,
		reflect, '*'), '-'));
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl + 1;
	newray.n = ray.n;
	newray.flag = ray.flag;
	return (newray);
}

t_ray		refraction(t_ray ray, t_vec3 norm, double n2)
{
	t_ray	newray;
	t_vec3	dir;
	double	c[2];
	double	s[2];

	c[0] = ft_dotproduct(norm, ray.dir);
	s[0] = sqrt(1 - c[0] * c[0]);
	s[1] = ray.n * (((double)s[0]) / n2);
	if (s[1] > 1)
	{
		newray.dir = ft_vec3_r(0, 0, 0);
		return (newray);
	}
	newray.org = ft_vec3vop_r(ft_vec3sop_r(ray.dir, (ray.dist + 0.000001),
		'*'), ray.org, '+');
	newray.n = n2;
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl + 1;
	newray.flag = ray.flag;
	c[1] = sqrt(1 - s[1] * s[1]);
	dir = ft_vec3normalize_r(ft_vec3vop_r(ray.dir, ft_vec3sop_r(norm,
		ft_dotproduct(ray.dir, norm), '*'), '-'));
	newray.dir = ft_vec3vop_r(ft_vec3sop_r(norm, -c[1], '*'),
		ft_vec3sop_r(dir, s[1], '*'), '+');
	return (newray);
}
