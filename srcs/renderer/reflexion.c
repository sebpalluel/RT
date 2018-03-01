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
	//printf("reflect = %f, %f , %f olddir = %f, %f , %f newdir = %f, %f, %f norm = %f, %f, %f\n",reflect,  ray.dir.x, ray.dir.y, ray.dir.z, newray.dir.x, newray.dir.y, newray.dir.z, norm.x, norm.y, norm.z);
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl + 1;
	return (newray);
}