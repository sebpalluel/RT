/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:17:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 11:23:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_bool			solve_quadratic(double *abc, float *t0, float *t1)
{
	float		discr;
	float		q;

	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (FALSE);
	else if (discr == 0)
		*t0 = -0.05 * abc[1] / abc[0];
	else
	{
		q = (abc[1] > 0) ? -0.5 * (abc[1] + sqrt(discr)) : -0.5 * \
			(abc[1] - sqrt(discr));
		*t0 = q / abc[0];
		*t1 = abc[2] / q;
	}
	if (t0 > t1)
		ft_swap(t0, t1, sizeof(float));
	return (TRUE);
}

t_bool			ft_solve_quadra(double abc[3], double *t)
{
	float		t0;
	float		t1;

	if (!solve_quadratic(abc, &t0, &t1))
		return (FALSE);
	if (t0 > t1)
		ft_swap(&t0, &t1, sizeof(float));
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (FALSE);
	}
	*t = t0;
	return (TRUE);
}

void			mult_dir_matrix(t_vec3 *src, t_vec3 *dst, double **x)
{
	double		a;
	double		b;
	double		c;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2];
	dst->x = a;
	dst->y = b;
	dst->z = c;
}

void			mult_vec3_matrix(t_vec3 src, t_vec3 *dst, double **x)
{
	double		a;
	double		b;
	double		c;
	double		w;

	a = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0] + x[3][0];
	b = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1] + x[3][1];
	c = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2] + x[3][2];
	w = src.x * x[0][3] + src.y * x[1][3] + src.z * x[2][3] + x[3][3];
	dst->x = a / w;
	dst->y = b / w;
	dst->z = c / w;
}

t_col			mult_scale_col_limited(double t, t_col col)
{
	col.r = col.r * t;
	col.g = col.g * t;
	col.b = col.b * t;
	if (col.r > 1)
		col.r = 1;
	if (col.g > 1)
		col.g = 1;
	if (col.b > 1)
		col.b = 1;
	return (col);
}
