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

void			ft_sort_pos(double *a, double *b, double *c)
{
	double tmp;

	if ((*a > *b && *b > 0) || *a < 0)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	if ((*b > *c && *c > 0) || *b < 0)
	{
		tmp = *c;
		*c = *b;
		*b = tmp;
	}
	if ((*a > *b && *b > 0) || *a < 0)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

int is_in_moeb(t_vec3 hitpoint, t_moebius moeb)
{
	double t;
	double s;
	double tmp;
	t_vec3 tmpvec;

	tmpvec = hitpoint;
	hitpoint.x = ft_vec3dot(tmpvec, moeb.axe_x);
	hitpoint.y = ft_vec3dot(tmpvec, moeb.axe_y);
	hitpoint.z = ft_vec3dot(tmpvec, ft_vec3vop_r(moeb.axe_x, moeb.axe_y, 'c'));	
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
	t_vec3	hitpoint;
	int i;

	dir = ft_vec3vop_r(ray.org, form->moeb.org, '-');
	o.x = ft_vec3dot(dir, form->moeb.axe_x);
	o.y = ft_vec3dot(dir, form->moeb.axe_y);
	o.z = ft_vec3dot(dir, ft_vec3vop_r(form->moeb.axe_x, form->moeb.axe_y, 'c'));
	hitpoint = ray.dir;
	dir.x = ft_vec3dot(hitpoint, form->moeb.axe_x);
	dir.y = ft_vec3dot(hitpoint, form->moeb.axe_y);
	dir.z = ft_vec3dot(hitpoint, ft_vec3vop_r(form->moeb.axe_x, form->moeb.axe_y, 'c'));
	abcd[0] = dir.x * dir.x * dir.y + dir.y * dir.y * dir.y 
	- 2 * dir.x * dir.x * dir.z - 2 * dir.y * dir.y * dir.z + dir.y * dir.z * dir.z;
	abcd[1] = calc(dir.x, o.x, dir.y, o.y) + 3 * dir.y * dir.y * o.y
	 - 2 * form->moeb.r * dir.x * dir.z - 2 * calc(dir.x, o.x, dir.z, o.z) - 2 * calc(dir.y, o.y, dir.z, o.z) + calc(dir.z, o.z, dir.y, o.y);
	abcd[2] = -form->moeb.r * form->moeb.r * dir.y + 2 * dir.x * o.x
	 * o.y + dir.y * o.x * o.x + 3 * dir.y * o.y * o.y - 2 * form->moeb.r * (o.x * dir.z + dir.x * o.z) - 2 * (2 * dir.x * o.x * o.z + dir.z * o.x * o.x) - 2 * (2 * dir.y * o.y * o.z + dir.z * o.y * o.y) + 2 * dir.z * o.z * o.y + dir.y * o.z * o.z;
	abcd[3] = -form->moeb.r * form->moeb.r * o.y + o.x * o.x * o.y + o.y * o.y * o.y - 2 * form->moeb.r * o.x * o.z - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z  + o.y * o.z * o.z;
	if (!ft_resolve_cubic_min(&abcd[0], &abcd[1], &abcd[2], abcd[3]))
		return (-1);
	ft_sort_pos(&abcd[0], &abcd[1], &abcd[2]);
	i = 0;
	while (i < 3)
	{
		if (abcd[i] < 0)
			return (-1);
		hitpoint = ft_vec3vop_r(ft_vec3sop_r(ray.dir, abcd[i], '*'), ray.org, '+');
		if (is_in_moeb(ft_vec3vop_r(hitpoint, form->moeb.org, '-'), form->moeb))
			return (abcd[i]);
		i++;
	}
	return (-1);
}

t_vec3			normal_moe(t_ray ray, t_list *moe)
{
	t_vec3 norm;
	t_vec3 hitpoint;
	t_vec3 tmpvec;
	double x;
	double y;
	double z;

	hitpoint = ft_vec3vop_r(ft_vec3vop_r(ft_vec3sop_r(ray.dir, ray.dist, '*'), ray.org, '+'), MOEB(moe).org, '-');
	norm = hitpoint;
	hitpoint.x = ft_vec3dot(norm, MOEB(moe).axe_x);
	hitpoint.y = ft_vec3dot(norm, MOEB(moe).axe_y);
	tmpvec = ft_vec3vop_r(MOEB(moe).axe_x, MOEB(moe).axe_y, 'c');
	hitpoint.z = ft_vec3dot(norm, tmpvec);
	x = hitpoint.x;
	y = hitpoint.y;
	z = hitpoint.z;
	norm = ft_vec3_r(2 * x * y - 2 * MOEB(moe).r * z - 4 * x * z,
		-MOEB(moe).r * MOEB(moe).r + x * x + 3 * y * y - 4 * y * z + z * z,
		-2 * MOEB(moe).r * x - 2 * x * x - 2 * y * y + 2 * y * z);
	hitpoint = ft_vec3normalize_r(norm);
	x = det_mat(MOEB(moe).axe_x, MOEB(moe).axe_y, tmpvec);
	norm.x = ft_vec3dot(hitpoint, ft_vec3_r(MOEB(moe).axe_y.y * tmpvec.z - tmpvec.y * MOEB(moe).axe_y.z, tmpvec.y * MOEB(moe).axe_x.z - MOEB(moe).axe_x.y * tmpvec.z, MOEB(moe).axe_x.y * MOEB(moe).axe_y.z - MOEB(moe).axe_y.y * MOEB(moe).axe_x.z));
	norm.y = ft_vec3dot(hitpoint, ft_vec3_r(-MOEB(moe).axe_y.x * tmpvec.z + tmpvec.x * MOEB(moe).axe_y.z, -tmpvec.x * MOEB(moe).axe_x.z + MOEB(moe).axe_x.x * tmpvec.z, -MOEB(moe).axe_x.x * MOEB(moe).axe_y.z + MOEB(moe).axe_y.x * MOEB(moe).axe_x.z));
	norm.z = ft_vec3dot(hitpoint, ft_vec3_r(MOEB(moe).axe_y.x * tmpvec.y - tmpvec.x * MOEB(moe).axe_y.y, tmpvec.x * MOEB(moe).axe_x.y - MOEB(moe).axe_x.x * tmpvec.y, MOEB(moe).axe_x.x * MOEB(moe).axe_y.y - MOEB(moe).axe_y.x * MOEB(moe).axe_x.y));
	if (ft_vec3dot(norm, ray.dir) > 0)
		norm = ft_vec3sop_r(norm, -1, '*');
//	hitpoint = norm;
//	norm.x = ft_vec3dot(hitpoint, MOEB(moe).axe_x);
//	norm.y = ft_vec3dot(hitpoint, MOEB(moe).axe_y);
//	norm.z = ft_vec3dot(hitpoint, ft_vec3vop_r(MOEB(moe).axe_x, MOEB(moe).axe_y, 'c'));
	return (norm);
}



t_col			intersec_moe(t_ray ray, t_list *moe, t_setup *setup)
{
	t_vec3		norm;

	if (ray.dist > 0.0)
	{
		norm = normal_moe(ray, moe);
//			return (ft_col_r(1,1,1,1));
//		printf("%f, %f, %f      %f, %f, %f\n", norm.x, norm.y, norm.z, ray.dir.x, ray.dir.y, ray.dir.z);
//		return (ft_col_r((norm.z + 1) / 2 , 0, 0, 1));
		return (diffuse(norm, moe, ray, FORM(moe)->mat));
	}
	return (setup->background);
}
