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
	return (newray);
}

/*
**  n1sin(i1) = n2sin(i2);
*/

t_ray		refraction(t_ray ray, t_vec3 norm, double n2)
{
	t_ray newray;
	double sini1;
	double sini2;
	double i2;

	sini1 = acos(ft_dotproduct(norm, ray.dir));
	sini2 = ray.n * sini1 / n2;
	if (fabs(sini2) > 1)
	{
		newray.dir = vec3_r(0,0,0);
		return (newray);
	}
	sini2;
	newray.org = ft_vec3vop_r(ft_vec3sop_r(ray.dir, (ray.dist + 0.00000001), '*'), ray.org, '+');
	newray.n = n2;
	
}