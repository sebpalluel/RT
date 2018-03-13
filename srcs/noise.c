/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/13 13:52:52 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

# define PERSISTANCE	0.75
# define FREQUENCY		0.02
# define LAYERS			5

double			ft_perlin(t_vec3 vec3)
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
		perlin += ft_perlin_noise(vec3.x * f + i, vec3.y * f + i, vec3.z * f + i) * amp;
		amp *= PERSISTANCE;
		f *= 2;
	}
	perlin *= (1 - PERSISTANCE) / (1 - amp);
	return (perlin);
}

void			ft_marble(t_vec3 vec3, t_col *to_col)
{
	double		perlin;
	double		marble;
	t_col		col[2];

	col[0] = ft_col_r(0.1, 0.1, 0.1, 1.);
	col[1] = ft_col_r(0.9, 0.9, 0.9, 1.);
	perlin = ft_perlin(vec3);
	marble = sqrt(fabs(sin(2 * M_PI * perlin)));
	*to_col = ft_coladd(ft_colmultscale(col[0], 1 - marble), \
				ft_colmultscale(col[1], marble));
}

void			ft_zebra(t_vec3 vec3, t_col *to_col)
{
	double		perlin;
	double		amp;
	double		zebra;
	t_col		col[2];

	amp = 200.;
	col[0] = ft_col_r(0.1, 0.1, 0.1, 1.);
	col[1] = ft_col_r(0.9, 0.9, 0.9, 1.);
	perlin = ft_perlin(vec3);
	zebra = (sin((vec3.x + perlin * amp) * 2 * M_PI / 200.f) + 1) / 2.f;
	*to_col = ft_col_r(zebra, zebra, zebra, 1.);
}

void			ft_wood(t_vec3 vec3, t_col *to_col)
{
	double		step;
	double		freq;
	double		perlin;
	double		wood;
	t_col		col[2];

	perlin = ft_perlin(vec3);
	step = 0.2;
	col[0] = ft_col_r(0.1, 0.1, 0.1, 1.);
	col[1] = ft_col_r(0.9, 0.9, 0.9, 1.);
	wood = fmod(perlin, step);
	if (wood > step / 2)
		wood = step - wood;
	freq = (1 - cos(M_PI * wood / (step / 2))) / 2;
	*to_col = ft_coladd(ft_colmultscale(col[0], 1 - freq), \
				ft_colmultscale(col[1], freq));
}

void			ft_cloud(t_vec3 vec3, t_col *to_col)
{
	double		cloud;
	t_col		col;
	double		amp;

	amp = 3.;
	col = ft_col_r(1, 1, 1, 1);
	cloud = ft_perlin(vec3);
	cloud = cos(((vec3.x * vec3.y * vec3.z) / (vec3.x * 2)) + cloud * amp);
	*to_col = ft_colmultscale(col, cloud);
}

void			ft_checker(t_vec3 vec3, t_col *to_col)
{
	int			xy_pos[2];
	int			freq;
	int			ixy[2];
	t_col		col[2];

	(void)vec3.z;
	col[0] = ft_col_r(0, 0, 0, 1);
	col[1] = ft_col_r(1, 1, 1, 1);
	ixy[0] = vec3.x;
	ixy[1] = vec3.y;
	freq = 10;
	xy_pos[0] = (vec3.x > 0) ? abs(ixy[0]) % (freq * 2) : \
				abs(ixy[0] - freq) % (freq * 2);
	xy_pos[1] = (vec3.y > 0) ? abs(ixy[1]) % (freq * 2) : \
				abs(ixy[1]) % (freq * 2);
	if (((xy_pos[0] < freq) && (xy_pos[1] < freq)) ||\
			((xy_pos[0] > freq) && (xy_pos[1] > freq)))
		*to_col = col[0];
	else
		*to_col = col[1];
}
