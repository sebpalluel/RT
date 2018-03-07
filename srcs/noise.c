/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/07 14:38:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

# define PERSISTANCE	0.75
# define FREQUENCY		0.1
# define OCTAVES		3

double			ft_perlin(double x, double y, double z)
{
	double		result;
	double		f;
	double		amplitude;
	int			i;
	int			t;

	result = 0;
	f = FREQUENCY;
	amplitude = 1;
	i = -1;
	while (++i < OCTAVES)
	{
		t = i * 4096;
		result += ft_perlin_noise(x * f + t, y * f + t, z * f + t) * amplitude;
		amplitude *= PERSISTANCE;
		f *= 2;
	}
	result *= (1 - PERSISTANCE) / (1 - amplitude);
	return (result);
}

void			perlin_draw_test(t_setup *setup, t_pix pix)
{
	float		perlin;

	perlin = ft_perlin((double)pix.x, (double)pix.y, (double)pix.z);
	ft_put_pixel(setup, pix.x, pix.y, ft_coltoi(ft_col_r(perlin, perlin, perlin, 1.)));
}
