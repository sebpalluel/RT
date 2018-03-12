/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/12 14:17:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

# define PERSISTANCE	0.75
# define FREQUENCY		0.02
# define LAYERS			5

double			ft_perlin(double x, double y, double z)
{
	double		perlin;
	double		f;
	double		amp;
	int			i;

	perlin = 0;
	f = FREQUENCY;
	amp = 1;
	i = -1;
	while (++i < LAYERS)
	{
		perlin += ft_perlin_noise(x * f + i, y * f + i, z * f + i) * amp;
		amp *= PERSISTANCE;
		f *= 2;
	}
	perlin *= (1 - PERSISTANCE) / (1 - amp);
	return (perlin);
}

t_col			ft_marble(double x, double y, double z)
{
	double		perlin;
	double		marble;
	t_col		col[2];

	col[0] = ft_col_r(0.1, 0.1, 0.1, 1.);
	col[1] = ft_col_r(0.9, 0.9, 0.9, 1.);
	perlin = ft_perlin(x, y, z);
	marble = sqrt(fabs(sin(2 * M_PI * perlin)));
	return (ft_coladd(ft_colmultscale(col[0], 1 - marble), \
				ft_colmultscale(col[1], marble)));
}

t_col			ft_zebra(double x, double y, double z)
{
	double		perlin;
	double		amp;
	double		zebra;
	t_col		col[2];

	amp = 200.;
	col[0] = ft_col_r(0.1, 0.1, 0.1, 1.);
	col[1] = ft_col_r(0.9, 0.9, 0.9, 1.);
	perlin = ft_perlin(x, y, z);
	zebra = (sin((x + perlin * amp) * 2 * M_PI / 200.f) + 1) / 2.f;
	return (ft_col_r(zebra, zebra, zebra, 1.));
}

t_col			ft_wood(double x, double y, double z)
{
	double		step;
	double		freq;
	double		perlin;
	double		wood;
	t_col		col[2];

	perlin = ft_perlin(x, y, z);
	step = 0.2;
	col[0] = ft_col_r(0.1, 0.1, 0.1, 1.);
	col[1] = ft_col_r(0.9, 0.9, 0.9, 1.);
	wood = fmod(perlin, step);
	if (wood > step / 2)
		wood = step - wood;
	freq = (1 - cos(M_PI * wood / (step / 2))) / 2;
	return (ft_coladd(ft_colmultscale(col[0], 1 - freq), \
				ft_colmultscale(col[1], freq)));
}

t_col			ft_cloud(double x, double y, double z)
{
	double		cloud;
	t_col		col;
	double		amp;

	amp = 3.;
	col = ft_col_r(1, 1, 1, 1);
	cloud = ft_perlin(x, y, z);
	cloud = cos(((x * y * z) / (x * 2)) + cloud * amp);
	return (ft_colmultscale(col, cloud));
}

t_col			ft_checker(double x, double y, double z)
{
	int			xy_pos[2];
	int			freq;
	int			ixy[2];
	t_col		col[2];

	(void)z;
	col[0] = ft_col_r(0, 0, 0, 1);
	col[1] = ft_col_r(1, 1, 1, 1);
	ixy[0] = x;
	ixy[1] = y;
	freq = 10;
	xy_pos[0] = (x > 0) ? abs(ixy[0]) % (freq * 2) : \
				abs(ixy[0] - freq) % (freq * 2);
	xy_pos[1] = (y > 0) ? abs(ixy[1]) % (freq * 2) : \
				abs(ixy[1]) % (freq * 2);
	if (((xy_pos[0] < freq) && (xy_pos[1] < freq)) ||\
			((xy_pos[0] > freq) && (xy_pos[1] > freq)))
		return (col[0]);
	else
		return (col[1]);
}
