/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:16:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/12 22:56:58 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

# define BLUR_SIZE 5

t_col		ft_hextocol(int hexvalue)
{
	t_col	col;

	col.r = ((hexvalue & 0xff0000) >> 16) / 255.;
	col.g = ((hexvalue & 0xff00) >> 8) / 255.;
	col.b = (hexvalue & 0xff) / 255.;
	col.s = 1.;
	return (col);
}

t_col		ft_get_pixel_col(t_setup *setup, int x, int y)
{
	int		tmp;
	size_t	index;

	index = (y * SCN.width) + x;
	tmp = ((int*)SCN.img[0]->image_addr)[index];
	return (ft_hextocol(tmp));
}

t_col		ft_cel_shading(t_setup *setup, int x, int y)
{
	float	index;
	float	clamp;
	t_col	col;

	index = 0;
	clamp = 0.1;
	col = ft_get_pixel_col(setup, x, y);
	while (index <= 1)
	{
		if (col.r >= index && col.r < index + clamp)
			col.r = index + (clamp / 2);
		if (col.g >= index && col.g < index + clamp)
			col.g = index + (clamp / 2);
		if (col.b >= index && col.b < index + clamp)
			col.b = index + (clamp / 2);
		index += clamp;
	}
	return (col);
}

t_col		ft_blur(t_setup *setup, int x, int y)
{
	t_col	avg;
	t_col	ref;
	int		xy_b[2];
	int		blurpix;

	avg = ft_col_r(0., 0., 0., 1.);
	blurpix = 0;
	xy_b[1] = y - 1;
	while (xy_b[1]++ < (int)SCN.height && xy_b[1] < (y + BLUR_SIZE))
	{
		xy_b[0] = x - 1;
		while (xy_b[0]++ < (int)SCN.width && xy_b[0] < (x + BLUR_SIZE))
		{
			ref = ft_get_pixel_col(setup, xy_b[0], xy_b[1]);
			avg.r += ref.r;
			avg.g += ref.g;
			avg.b += ref.b;
			blurpix++;
		}
	}
	return (ft_col_r(avg.r / blurpix, avg.g / blurpix, avg.b / blurpix, 1.));
}

t_col		ft_sepia(t_setup *setup, int x, int y)
{
	float	red;
	float	green;
	float	blue;
	t_col	col;

	col = ft_get_pixel_col(setup, x, y);
	if ((red = (col.r * 0.393) + (col.g * 0.769) + (col.b * 0.189)) > 1.)
		red = 1.;
	if ((green = (col.r * 0.349) + (col.g * 0.686) + (col.b * 0.168)) > 1.)
		green = 1.;
	if ((blue = (col.r * 0.272) + (col.g * 0.534) + (col.b * 0.131)) > 1.)
		blue = 1.;
	return (ft_col_r(red, green, blue, 1.));
}

t_col		ft_blackandwhite(t_setup *setup, int x, int y)
{
	double	tmp;
	t_col	col;

	col = ft_get_pixel_col(setup, x, y);
	tmp = (col.r + col.g + col.b) / 3.;
	return (ft_col_r(tmp, tmp, tmp, 1.));
}

t_col		ft_negative(t_setup *setup, int x, int y)
{
	t_col	col;

	col = ft_get_pixel_col(setup, x, y);
	return (ft_col_r(1 - col.r, 1 - col.g, 1 - col.b, 1.));
}

void		ft_effect_change(t_setup *setup, int effect)
{
	int		x;
	int		y;

	if ((SCN.effect = effect ? TRUE : FALSE))
	{
		ft_imgclean(SCN.img[1], SCN.width, SCN.height);
		y = -1;
			while (y++ < (int)SCN.height)
			{
				x = -1;
				while (x++ < (int)SCN.width)
					ft_put_pixel(setup, x, y, \
							ft_coltoi(postprocess()[effect - 1](setup, x, y)));
			}
	}
	mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
			SCN.img[SCN.effect]->image, 0, 0);
}
