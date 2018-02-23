/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:17:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 16:19:18 by psebasti         ###   ########.fr       */
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
