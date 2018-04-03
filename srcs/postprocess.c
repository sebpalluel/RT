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

#define BLUR_SIZE 5

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
