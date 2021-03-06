/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 16:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/04/03 20:45:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double	hit_cyl(t_ray ray, t_shape *form)
{
	double a;
	double b;
	double c;
	double delta;
	t_vec3 tmp;

	tmp = ft_vec3vop_r(form->cyl.dir, ray.dir, 'c');
	a = ft_vec3dot(tmp, tmp);
	b = 2.0 * ft_vec3dot(tmp, ft_vec3vop_r(form->cyl.dir, \
				ft_vec3vop_r(ray.org, form->cyl.pos, '-'), 'c'));
	tmp = ft_vec3vop_r(form->cyl.dir, \
			ft_vec3vop_r(ray.org, form->cyl.pos, '-'), 'c');
	c = ft_vec3dot(tmp, tmp) - form->cyl.r * form->cyl.r;
	if (a == 0 && b != 0)
		return (-1.0);
	delta = b * b - 4.0 * a * c;
	if (delta <= 0.0)
		return (-1.0);
	if ((c = (-b - sqrt(delta)) / (2.0 * a)) > 0)
		return (c);
	else
		return ((-b + sqrt(delta)) / (2.0 * a));
}

t_vec3	normal_cyl(t_ray ray, t_list *cyl)
{
	t_vec3 hit;
	t_vec3 oc;
	double height;
	t_vec3 norm;

	hit = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	oc = ft_vec3vop_r(hit, CYLI(cyl).pos, '-');
	height = ft_vec3dot(CYLI(cyl).dir, oc);
	norm = ft_vec3normalize_r(ft_vec3vop_r(oc, \
				ft_vec3sop_r(CYLI(cyl).dir, height, '*'), '-'));
	return (norm);
}

t_col	intersec_cyl(t_ray ray, t_list *cyl, t_setup *setup)
{
	t_vec3		norm;

	if (ray.dist >= 0.0)
	{
		norm = normal_cyl(ray, cyl);
		return (diffuse(norm, cyl, ray, FORM(cyl)->mat));
	}
	return (setup->background);
}
