/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/03/19 17:17:18 by psebasti         ###   ########.fr       */
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
	else if (a > b && b < 0)
		return (a);
	else
		return (b);
}

int is_in_moeb(t_vec3 hitpoint, t_moebius moeb)
{
	double t;
	double s;
	double tmp;

	t = atan2(hitpoint.y, hitpoint.x);
	tmp = sin(t / 2.0);
	if (fabs(tmp) > 0.000001)
		s = hitpoint.z / tmp;
	else if (fabs(tmp = cos(t)) > 0.000001)
		s = (hitpoint.x / tmp - moeb.r) / cos(t / 2.0);
	else
		s = (hitpoint.y / sin(t) - moeb.r) / cos(t / 2.0);

	hitpoint.x -= (moeb.r + s * cos(t / 2.0)) * cos(t);
	hitpoint.y -= (moeb.r + s * cos(t / 2.0)) * sin(t);
	hitpoint.z -= s * sin(t / 2.0);

	if (ft_vec3dot(hitpoint, hitpoint) >= 0.000001)
		return (0);
	return (s >= -(moeb.width / 2.0 - 0.000001) && s <= moeb.width / 2.0 + 0.000001);
}

double			hit_moe(t_ray ray, t_shape *form)
{
	double 	abcd[4];
	t_vec3	dir;
	t_vec3	o;
	double	r;
	t_vec3	hitpoint;

	o = ft_vec3vop_r(ray.org, form->moeb.org, '-');
	dir = ray.dir;
	abcd[0] = dir.x * dir.x * dir.y + dir.y * dir.y * dir.y - 2 * dir.x * dir.x * dir.z - 2 * dir.y * dir.y * dir.z + dir.y * dir.z * dir.z;
	abcd[1] = calc(dir.x, o.x, dir.y, o.y) + 3 * dir.y * dir.y * o.y - 2 * form->moeb.r * dir.x * dir.z - 2 * calc(dir.x, o.x, dir.z, o.z) - 2 * calc(dir.y, o.y, dir.z, o.z) + calc(dir.z, o.z, dir.y, o.y);
	abcd[2] = -form->moeb.r * form->moeb.r * dir.y + 2 * dir.x * o.x * o.y + dir.y * o.x * o.x + 3 * dir.y * o.y * o.y - 2 * form->moeb.r * (o.x * dir.z + dir.x * o.z) - 2 * (2 * dir.x * o.x * o.z + dir.z * o.x * o.x) - 2 * (2 * dir.y * o.y * o.z + dir.z * o.y * o.y) + 2 * dir.z * o.z * o.y + dir.y * o.z * o.z;
	abcd[3] = -form->moeb.r * form->moeb.r * o.y + o.x * o.x * o.y + o.y * o.y * o.y - 2 * form->moeb.r * o.x * o.z - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z  + o.y * o.z * o.z;

//	printf("abcd %f, %f, %f, %f\n", abcd[0], abcd[1], abcd[2], abcd[3]);
	r = ft_resolve_cubic_min(abcd[0], abcd[1], abcd[2], abcd[3]);
//	r = -1;
//	printf("%f\n",  ft_resolve_cubic_min(-0.480021, 2.088344, -0.447720, -3.954325));
	//printf("test %f\n", ft_2min_pos(1, -1));
	if (r < 0)
	{
//		printf("%f abcd %fx^3 + %fx^2 + %fx + %f\n", r, abcd[0], abcd[1], abcd[2], abcd[3]);
		return (-1);
	}


	hitpoint = ft_vec3vop_r(ft_vec3sop_r(ray.dir, r, '*'), ray.org, '+');
//	printf("%f\n", form->moeb.r);
//	printf("%f, %f, %f\n", form->moeb.org.x, form->moeb.org.y, form->moeb.org.z);
//	printf("%f, %f, %f\n", hitpoint.x, hitpoint.y, hitpoint.z);
//	printf("%f\n", ft_resolve_cubic_min(-1, 1, 1, -0.2));
	if (is_in_moeb(ft_vec3vop_r(hitpoint, form->moeb.org, '-'), form->moeb))
		return (r);
//		double i = hit_moe(init_ray(ft_vec3vop_r(hitpoint, ft_vec3sop_r(ray.dir, 0.00000001, '*'), '+'), ray.dir), form);
//		if (i > 0)
//			printf("%f\n", i);
	if (r > 0)
	{
		abcd[0] = hit_moe(init_ray(ft_vec3vop_r(hitpoint, ft_vec3sop_r(ray.dir, 0.0001, '*'), '+'), ray.dir), form);
//		hitpoint = ft_vec3vop_r(ft_vec3sop_r(ray.dir, r + abcd[0], '*'), ray.org, '+');

			//printf("abcd %f\n", r + abcd[0]);
		if (abcd[0] > 0)
			return (r + abcd[0]);
	}
	return (-1);
}

t_vec3			normal_moe(t_ray ray, t_list *moe)
{
	t_vec3 norm;
	t_vec3 hitpoint;
	double x;
	double y;
	double z;

	hitpoint = ft_vec3vop_r(ft_vec3vop_r(ft_vec3sop_r(ray.dir, ray.dist, '*'), ray.org, '+'), MOEB(moe).org, '-');
	x = hitpoint.x;
	y = hitpoint.y;
	z = hitpoint.z;
	norm = ft_vec3_r(2 * x * y - 2 * MOEB(moe).r * z - 4 * x * z, -MOEB(moe).r * MOEB(moe).r + x * x + 3 * y * y - 4 * y * z + z * z, -2 * MOEB(moe).r * x - 2 * x * x - 2 * y * y + 2 * y * z);
	norm = ft_vec3normalize_r(norm);
	if (ft_vec3dot(norm, ray.dir) > 0)
		norm = ft_vec3sop_r(norm, -1, '*');
	return (norm);

}



t_col			intersec_moe(t_ray ray, t_list *moe, t_setup *setup)
{
	t_vec3		norm;
//(void)moe;

	if (ray.dist > 0.0)
	{
		norm = normal_moe(ray, moe);
//		printf("%f\n", ray.dist);
//		if (ray.dist == 3)
//			return (ft_col_r(0, 1, 0, 0));
//		return(ft_col_r(1, ray.dist / 3, 0, 0));
		return (diffuse(norm, moe, ray, FORM(moe)->mat));
	}
	return (setup->background);
}
