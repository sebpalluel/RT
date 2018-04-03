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

static inline double		calc(double x, double ox, double y, double oy)
{
	return (x * x * oy + 2 * x * y * ox);
}

void						ft_sort_pos(double *a, double *b, double *c)
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

int							is_in_moeb(t_vec3 hitpoint, t_moebius moeb)
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
	return (s >= -(moeb.width / 2.0 - 0.000001) &&
		s <= moeb.width / 2.0 + 0.000001);
}

t_vec3						change_base(t_vec3 a, t_vec3 x, t_vec3 y)
{
	t_vec3 tmp;

	tmp = a;
	a.x = ft_vec3dot(tmp, x);
	a.y = ft_vec3dot(tmp, y);
	a.z = ft_vec3dot(tmp, ft_vec3vop_r(x, y, 'c'));
	return (a);
}

void						moeb_equ(t_vec3 o, t_vec3 d, double r,
												double *(abcd[4]))
{
	*abcd[0] = d.x * d.x * d.y + d.y * d.y * d.y - 2 * d.x *
		d.x * d.z - 2 * d.y * d.y * d.z + d.y * d.z * d.z;
	*abcd[1] = calc(d.x, o.x, d.y, o.y) + 3 * d.y * d.y * o.y
		- 2 * r * d.x * d.z - 2 * calc(d.x, o.x, d.z, o.z) -
		2 * calc(d.y, o.y, d.z, o.z) + calc(d.z, o.z, d.y, o.y);
	*abcd[2] = -r * r * d.y + 2 * d.x * o.x * o.y
		+ d.y * o.x * o.x + 3 * d.y * o.y * o.y - 2 * r * (o.x * d.z +
		d.x * o.z) - 2 * (2 * d.x * o.x * o.z + d.z * o.x * o.x) - 2 * (2 *
		d.y * o.y * o.z + d.z * o.y * o.y) + 2 * d.z * o.z * o.y + d.y * o.z
		* o.z;
	*abcd[3] = -r * r * o.y + o.x * o.x * o.y + o.y * o.y * o.y
		- 2 * r * o.x * o.z - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z
		+ o.y * o.z * o.z;
}

double						hit_moe(t_ray ray, t_shape *form)
{
	double	abcd[4];
	t_vec3	d;
	t_vec3	o;
	t_vec3	hitpoint;
	int		i;

	o = change_base(ft_vec3vop_r(ray.org, form->moeb.org, '-'),
		form->moeb.axe_x, form->moeb.axe_y);
	d = change_base(ray.dir, form->moeb.axe_x, form->moeb.axe_y);
	hitpoint = ray.dir;
	moeb_equ(o, d, form->moeb.r, (double *(*))&abcd);
	if (!ft_resolve_cubic_min(&abcd[0], &abcd[1], &abcd[2], abcd[3]))
		return (-1);
	ft_sort_pos(&abcd[0], &abcd[1], &abcd[2]);
	i = -1;
	while (++i < 3)
	{
		if (abcd[i] < 0)
			return (-1);
		hitpoint = ft_vec3vop_r(ft_vec3sop_r(ray.dir, abcd[i], '*'),
			ray.org, '+');
		if (is_in_moeb(ft_vec3vop_r(hitpoint, form->moeb.org, '-'), form->moeb))
			return (abcd[i]);
	}
	return (-1);
}

t_vec3						norm_moeb(t_vec3 x, t_vec3 y, t_vec3 norm)
{
	t_vec3 z;

	z = ft_vec3vop_r(x, y, 'c');
	norm = change_base(norm, ft_vec3_r(y.y * z.z - z.y * y.z, z.y *
		x.z - x.y * z.z, x.y * y.z - y.y * x.z),
		ft_vec3_r(-y.x * z.z + z.x * y.z, -z.x *
		x.z + x.x * z.z, -x.x * y.z + y.x * x.z));
	return (norm);
}

t_vec3						normal_moe(t_ray ray, t_list *moe)
{
	t_vec3 norm;
	t_vec3 hitpoint;
	t_vec3 tmpvec;
	t_vec3 t;

	hitpoint = ft_vec3vop_r(ft_vec3vop_r(ft_vec3sop_r(ray.dir, ray.dist, '*'),
		ray.org, '+'), MOEB(moe).org, '-');
	hitpoint = change_base(hitpoint, MOEB(moe).axe_x, MOEB(moe).axe_y);
	tmpvec = ft_vec3vop_r(MOEB(moe).axe_x, MOEB(moe).axe_y, 'c');
	t = hitpoint;
	norm = ft_vec3_r(2 * t.x * t.y - 2 * MOEB(moe).r * t.z - 4 * t.x * t.z,
		-MOEB(moe).r * MOEB(moe).r + t.x * t.x + 3 * t.y * t.y - 4 * t.y * t.z +
		t.z * t.z,
		-2 * MOEB(moe).r * t.x - 2 * t.x * t.x - 2 * t.y * t.y + 2 * t.y * t.z);
	norm = norm_moeb(MOEB(moe).axe_x, MOEB(moe).axe_y, norm);
	if (ft_vec3dot(norm, ray.dir) > 0)
		norm = ft_vec3sop_r(norm, -1, '*');
	return (norm);
}

t_col						intersec_moe(t_ray ray, t_list *moe, t_setup *setup)
{
	t_vec3		norm;

	if (ray.dist > 0.0)
	{
		norm = normal_moe(ray, moe);
		return (diffuse(norm, moe, ray, FORM(moe)->mat));
	}
	return (setup->background);
}
