/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:16:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/12 21:27:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

# define BLUR_SIZE 5

t_col			ft_hextocol(int hexvalue)
{
	t_col		col;

	col.r = ((hexvalue & 0xff0000) >> 16) / 255.;
	col.g = ((hexvalue & 0xff00) >> 8) / 255.;
	col.b = (hexvalue & 0xff) / 255.;
	col.s = 1.;
	return (col);
}

t_col			ft_get_pixel_col(t_setup *setup, int x, int y)
{
	int			tmp;
	size_t		index;

	index = (y * SCN.width) + x;
	tmp = ((int*)SCN.img[0]->image_addr)[index];
	return (ft_hextocol(tmp));
}

t_col			ft_cel_shading(t_col col)
{
	float		index;
	float		clamp;

	index = 0;
	clamp = 0.1;
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

t_col			calc_blur_avg(t_setup *setup, int xy[2])
{
	t_col		avg;
	t_col		ref;
	int			xy_b[2];
	int			blurpix;

	avg = ft_col_r(0., 0., 0., 1.);
	blurpix = 0;
	xy_b[1] = xy[1] - 1;
	while (xy_b[1]++ < (int)SCN.height && xy_b[1] < (xy[1] + BLUR_SIZE))
	{
		xy_b[0] = xy[0] - 1;
		while (xy_b[0]++ < (int)SCN.width && xy_b[0] < (xy[0] + BLUR_SIZE))
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

void			ft_blur(t_setup *setup)
{
	int			xy[2];

	xy[1] = -1;
	while(xy[1]++ < (int)SCN.height)
	{
		xy[0] = -1;
		while(xy[0]++ < (int)SCN.width)
			ft_put_pixel(setup, xy[0], xy[1], ft_coltoi(\
						calc_blur_avg(setup, xy)));
	}
}

t_col		ft_sepia(t_col col)
{
	float	red;
	float	green;
	float	blue;

	red = (col.r * 0.393) + (col.g * 0.769) + (col.b * 0.189);
	green = (col.r * 0.349) + (col.g * 0.686) + (col.b * 0.168);
	blue = (col.r * 0.272) + (col.g * 0.534) + (col.b * 0.131);
	return (ft_col_r(red, green, blue, 1.));
}

void		ft_effect_change(t_setup *setup, int effect)
{
	int		x;
	int		y;

	if ((SCN.effect = effect ? TRUE : FALSE))
	{
		ft_imgclean(SCN.img[1], SCN.width, SCN.height);
		y = -1;
		if (effect == 3)
			ft_blur(setup);
		else
			while (y++ < (int)SCN.height)
			{
				x = -1;
				while (x++ < (int)SCN.width)
					ft_put_pixel(setup, x, y, ft_coltoi(ft_cel_shading(ft_get_pixel_col(setup, x, y))));
			}
	}
	mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
			SCN.img[SCN.effect]->image, 0, 0);
}
