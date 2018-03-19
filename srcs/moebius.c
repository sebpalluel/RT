/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/03/19 17:11:58 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline double	calc(double x, double ox, double y, double oy)
{
	return (x * x * oy + 2 * x * y * ox);
}

double			ft_2min_pos(double a, double b)
{
	if (a < b && a > 0)
		return (a);
	else
		return (b);
}

int is_in_moeb(double r, t_moebius moeb, t_ray ray)
{
	t_vec3	hitpoint;
	t_vec3	proj_circ;
	double	dist;

	hitpoint = ft_vec3vop_r(ft_vec3sop_r(ray.dir, r, '*'), ray.org, '+');

	proj_circ = ft_vec3vop_r(hitpoint, ft_vec3sop_r(moeb.axe_x, ft_dotproduct(moeb.axe_x, hitpoint), '*'), '-');
	proj_circ = ft_vec3normalize_r(proj_circ);
	proj_circ = ft_vec3sop_r(proj_circ, moeb.r, '*');
	proj_circ = ft_vec3vop_r(proj_circ, ft_vec3sop_r(moeb.axe_x, ft_dotproduct(moeb.axe_x, moeb.org), '*'), '+');
	dist = ft_vec3norm(ft_vec3vop_r(proj_circ, hitpoint, '-'));
	if (dist < moeb.width / 2.0)
		return (1);
	return (0);
}

double			hit_moe(t_ray ray, t_shape *form)
{
	double 	abcd[4];
	t_vec3	dir;
	t_vec3	o;
	double	r;

	o = ft_vec3vop_r(ray.org, form->moeb.org, '-');
	dir = ray.dir;
	//	torus.dir = dir;
	//	torus.org = shape.org;
	//	torus.bradius = shape.radius;
	//	torus.sradius = shape.height / 2.0;
	abcd[0] = dir.x * dir.x * dir.y + dir.y * dir.y * dir.y - 2 * dir.x * dir.x * dir.z - 2 * dir.y * dir.y * dir.z + dir.y * dir.z * dir.z;
	abcd[1] = calc(dir.x, o.x, dir.y, o.y) + 3 * dir.y * dir.y * o.y - 2 * form->moeb.r * dir.x * dir.y - 2 * calc(dir.x, o.x, dir.z, o.z) - 2 * calc(dir.y, o.y, dir.z, o.z) + calc(dir.z, o.z, dir.y, o.y);
	abcd[2] = -form->moeb.r * form->moeb.r * dir.y + 2 * dir.x * o.x * o.y + dir.y * o.x * o.x + 3 * dir.y * o.y * o.y - 2 * form->moeb.r * (o.x * dir.y + dir.x * o.y) - 2 * (2 * dir.x * o.x * o.z + dir.z * o.x * o.x) - 2 * (2 * dir.y * o.y * o.z + dir.z * o.y * o.y) + 2 * dir.z * o.z * o.y + dir.y * o.z * o.z;
	abcd[3] = -form->moeb.r * form->moeb.r * o.y + o.x * o.x * o.y + o.y * o.y * o.y - 2 * form->moeb.r * o.x * o.y - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z  + o.y * o.z * o.z;

	r = ft_resolve_cubic_min(abcd[0], abcd[1], abcd[2], abcd[3]);
	if (r < 0)
		return (-1);
	if (is_in_moeb(r, form->moeb, ray))
		return (r);
	return (-1);
}

t_col			intersec_moe(t_ray ray, t_list *moe, t_setup *setup)
{
//	t_vec3		norm;
(void)moe;

	if (ray.dist >= 0.0)
	{
		//		norm = normal_sphere(ray, moe);
		printf("test");
		return(ft_col_r(1, 1, 0, 0));
//		return (diffuse(norm, moe, ray, FORM(moe)->mat));
	}
	return (setup->background);
}
