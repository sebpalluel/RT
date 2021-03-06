/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:59:10 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/02 17:34:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void				ft_put_pixel(t_setup *setup, int x, int y, int color)
{
	int			*tmp;
	size_t		index;

	if (y >= (int)SCN.height || x >= (int)SCN.width || x < 0 || y < 0)
		return ;
	index = (y * SCN.width) * (SCN.img[SCN.effect]->bbp >> 3) \
			+ x * (SCN.img[SCN.effect]->bbp >> 3);
	tmp = (int *)&SCN.img[SCN.effect]->image_addr[index];
	*tmp = color;
}

double				ft_doublescale(double num, double in[2], double scale[2])
{
	double		rate;
	double		offset;

	rate = (scale[1] - scale[0]) / (in[1] - in[0]);
	offset = scale[0] - (in[0] * rate);
	return ((num * rate) + offset);
}

void				ft_sinvalintime(double *val, double min, double max,\
		double speed)
{
	double			in[2];
	double			scale[2];

	in[0] = -1;
	in[1] = 1;
	scale[0] = min;
	scale[1] = max;
	g_time += 1;
	*val = ft_doublescale(sin(g_time * speed), in, scale);
}

void				ft_cosvalintime(double *val, double min, double max,\
		double speed)
{
	double			in[2];
	double			scale[2];

	in[0] = -1;
	in[1] = 1;
	scale[0] = min;
	scale[1] = max;
	g_time += 1;
	*val = ft_doublescale(cos(g_time * speed), in, scale);
}
