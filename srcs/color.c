/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 04:50:31 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 16:04:14 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_col		addcol(t_col col1, t_col col2)
{
	t_col	col;

	col.r = col1.r + col2.r;
	if (col.r > 1)
		col.r = 1;
	col.g = col1.g + col2.g;
	if (col.g > 1)
		col.g = 1;
	col.b = col1.b + col2.b;
	if (col.b > 1)
		col.b = 1;
	return (col);
}

t_col		mult_scale_col(double t, t_col col)
{
	col.r = col.r * t;
	col.g = col.g * t;
	col.b = col.b * t;
	return (col);
}

t_col		multcol(t_col col1, t_col col2)
{
	t_col	col;

	col.r = col1.r * col2.r;
	col.g = col1.g * col2.g;
	col.b = col1.b * col2.b;
	return (col);
}

t_col		init_col(double r, double g, double b, double s)
{
	t_col	col;

	col.r = r;
	col.g = g;
	col.b = b;
	col.s = s;
	return (col);
}

t_col		interpolcol(t_col col1, t_col col2, double t)
{
	t_col	col;

	col.r = col1.r * (1 - t) + col2.r * t;
	col.g = col1.g * (1 - t) + col2.g * t;
	col.b = col1.b * (1 - t) + col2.b * t;
	return (col);
}
