/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:16:45 by psebasti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/04/01 19:20:24 by mbeilles         ###   ########.fr       */
=======
/*   Updated: 2018/03/29 17:09:34 by psebasti         ###   ########.fr       */
>>>>>>> bf13c177fd8325d040d5a563cbab82d22e7954d7
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

# define BLUR_SIZE 5

SDL_Surface			*ft_cel_shading(SDL_Surface *s)
{
	/*float			index;*/
	/*float			clamp;*/
	/*t_col			col;*/
	/*int				xy[2];*/

	/*index = 0;*/
	/*clamp = 0.1;*/
	/*col = ft_get_pixel_col(setup, x, y);*/
	/*while (index <= 1)*/
	/*{*/
		/*if (col.r >= index && col.r < index + clamp)*/
			/*col.r = index + (clamp / 2);*/
		/*if (col.g >= index && col.g < index + clamp)*/
			/*col.g = index + (clamp / 2);*/
		/*if (col.b >= index && col.b < index + clamp)*/
			/*col.b = index + (clamp / 2);*/
		/*index += clamp;*/
	/*}*/
	/*return (col);*/
	return (s);
}

SDL_Surface			*ft_blur(SDL_Surface *s)
{
	/*t_col			avg;*/
	/*t_col			ref;*/
	/*int				xy_b[2];*/
	/*int				blurpix;*/

	/*avg = ft_col_r(0., 0., 0., 1.);*/
	/*blurpix = 0;*/
	/*xy_b[1] = y - 1;*/
	/*while (xy_b[1]++ < (int)SCN.height && xy_b[1] < (y + BLUR_SIZE))*/
	/*{*/
		/*xy_b[0] = x - 1;*/
		/*while (xy_b[0]++ < (int)SCN.width && xy_b[0] < (x + BLUR_SIZE))*/
		/*{*/
			/*ref = ft_get_pixel_col(setup, xy_b[0], xy_b[1]);*/
			/*avg.r += ref.r;*/
			/*avg.g += ref.g;*/
			/*avg.b += ref.b;*/
			/*blurpix++;*/
		/*}*/
	/*}*/
	return (s);
	/*return (ft_col_r(avg.r / blurpix, avg.g / blurpix, avg.b / blurpix, 1.));*/
}

<<<<<<< HEAD
SDL_Surface			*ft_sepia(SDL_Surface *s)
{
	/*float			red;*/
	/*float			green;*/
	/*float			blue;*/
	/*t_col			col;*/

	/*col = ft_get_pixel_col(setup, x, y);*/
	/*if ((red = (col.r * 0.393) + (col.g * 0.769) + (col.b * 0.189)) > 1.)*/
		/*red = 1.;*/
	/*if ((green = (col.r * 0.349) + (col.g * 0.686) + (col.b * 0.168)) > 1.)*/
		/*green = 1.;*/
	/*if ((blue = (col.r * 0.272) + (col.g * 0.534) + (col.b * 0.131)) > 1.)*/
		/*blue = 1.;*/
	return (s);
	/*return (ft_col_r(red, green, blue, 1.));*/
}

SDL_Surface			*ft_blackandwhite(SDL_Surface *s)
=======
t_col		ft_cel_shading(SDL_Surface *s, int x, int y)
{
	float	index;
	float	clamp;
	t_col	col;

	index = 0;
	clamp = 0.1;
	col = get_pixel_col(s, x, y);
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

t_col		ft_blur(SDL_Surface *s, int x, int y)
>>>>>>> bf13c177fd8325d040d5a563cbab82d22e7954d7
{
	t_rect			r;
	uint8_t			t;
	uint32_t		p;

<<<<<<< HEAD
	r = (t_rect){~0U, ~0U, 0, 0};
	while (++r.x < s->w)
	{
		r.y = ~0U;
		while (++r.y < s->h)
		{
			p = get_pixel(s, r.x, r.y);
			t = (get_pixel_blue(p) + get_pixel_green(p) + get_pixel_red(p)) / 3;
			set_pixel(s, r.x, r.y, create_color(t, t, t, get_pixel_alpha(p)));
		}
	}
	return (s);
}

SDL_Surface			*ft_negative(SDL_Surface *s)
{
	t_rect			r;

	r = (t_rect){~0U, ~0U, 0, 0};
	while (++r.x < s->w)
	{
		r.y = ~0U;
		while (++r.y < s->h)
			set_pixel(s, r.x, r.y, ~(get_pixel(s, r.x, r.y) & 0x00ffffff)
									+ (get_pixel(s, r.x, r.y) & 0xff000000));
	}
	return (s);
=======
	avg = ft_col_r(0., 0., 0., 1.);
	blurpix = 0;
	xy_b[1] = y - 1;
	while (xy_b[1]++ < (int)s->h && xy_b[1] < (y + BLUR_SIZE))
	{
		xy_b[0] = x - 1;
		while (xy_b[0]++ < (int)s->w && xy_b[0] < (x + BLUR_SIZE))
		{
			ref = get_pixel_col(s, xy_b[0], xy_b[1]);
			avg.r += ref.r;
			avg.g += ref.g;
			avg.b += ref.b;
			blurpix++;
		}
	}
	return (ft_col_r(avg.r / blurpix, avg.g / blurpix, avg.b / blurpix, 1.));
}

t_col		ft_sepia(SDL_Surface *s, int x, int y)
{
	float	red;
	float	green;
	float	blue;
	t_col	col;

	col = get_pixel_col(s, x, y);
	if ((red = (col.r * 0.393) + (col.g * 0.769) + (col.b * 0.189)) > 1.)
		red = 1.;
	if ((green = (col.r * 0.349) + (col.g * 0.686) + (col.b * 0.168)) > 1.)
		green = 1.;
	if ((blue = (col.r * 0.272) + (col.g * 0.534) + (col.b * 0.131)) > 1.)
		blue = 1.;
	return (ft_col_r(red, green, blue, 1.));
}

t_col		ft_blackandwhite(SDL_Surface *s, int x, int y)
{
	double	tmp;
	t_col	col;

	col = get_pixel_col(s, x, y);
	tmp = (col.r + col.g + col.b) / 3.;
	return (ft_col_r(tmp, tmp, tmp, 1.));
}

t_col		ft_negative(SDL_Surface *s, int x, int y)
{
	t_col	col;

	col = get_pixel_col(s, x, y);
	return (ft_col_r(1 - col.r, 1 - col.g, 1 - col.b, 1.));
>>>>>>> bf13c177fd8325d040d5a563cbab82d22e7954d7
}
