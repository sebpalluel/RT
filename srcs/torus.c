/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 10:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/03/19 16:35:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double			hit_tor(t_ray ray, t_shape *shape)
{
	return (-1);
	(void)ray;
	(void)shape;

	t_vec3	o;
	t_vec3	d;
	double	abcde[5];
	double	tmp[6];
	double	r;

	o = ft_vec3vop_r(ray.org, shape->tor.org, '-');
	d = ray.dir;
	tmp[0] = d.x * d.x + d.y * d.y + d.z * d.z;
	tmp[1] = 2 * (o.x * d.x + o.y * d.y + o.z * d.z);
	tmp[2] = o.x * o.x + o.y * o.y + o.z * o.z + 
		(shape->tor.b_r) * (shape->tor.b_r) - 
		(shape->tor.s_r) * (shape->tor.s_r);
	tmp[3] = (d.x * d.x + d.y * d.y) * 4 * 
		(shape->tor.b_r) * (shape->tor.b_r);
	tmp[4] = 8 * (shape->tor.b_r) * 
		(shape->tor.b_r) * (o.x * d.x + o.y * d.y);
	tmp[5] = 4 * (shape->tor.b_r) * 
		(shape->tor.b_r) * (o.x * o.x + o.y * o.y);
	abcde[0] = tmp[0] * tmp[0];
	abcde[1] = 2 * tmp[1] * tmp[0] / abcde[0];
	abcde[2] = (2 * tmp[0] * tmp[2] + tmp[1] * tmp[1] - tmp[3]) / abcde[0];
	abcde[3] = (2 * tmp[1] * tmp[2] - tmp[4]) / abcde[0];
	abcde[4] = (tmp[2] * tmp[2] - tmp[5]) / abcde[0];
	r = ft_resolve_quadric_min(abcde[1], abcde[2], abcde[3], abcde[4]);
//	printf("%f\n", r);
//	printf("%lf\n", ft_resolve_quadric_min(-1, 1, 1, 1));
	return (r);
}

t_col			intersec_tor(t_ray ray, t_list *torus, t_setup *setup)
{
	//t_vec3		norm;
	(void)torus;
	if (ray.dist >= 0.0)
	{
		printf("%f\n", ray.dist);
		//norm = normal_sphere(ray, torus);
		//return (diffuse(norm, sph, ray, FORM(torus)->mat));
		return (ft_col_r((ray.dist - 1) / 2, 0, 0, 0));
	}
	return (setup->background);
}
