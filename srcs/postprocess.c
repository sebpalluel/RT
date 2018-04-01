/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:16:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/01 19:20:24 by mbeilles         ###   ########.fr       */
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
{
	t_rect			r;
	uint8_t			t;
	uint32_t		p;

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
}

//void		ft_effect_change(t_setup *setup, int effect)
//{
//	int		x;
//	int		y;
//
//	if ((SCN.effect = effect ? TRUE : FALSE))
//	{
//		ft_imgclean(SCN.img[1], SCN.width, SCN.height);
//		y = -1;
//			while (y++ < (int)SCN.height)
//			{
//				x = -1;
//				while (x++ < (int)SCN.width)
//					ft_put_pixel(setup, x, y, \
//							ft_coltoi(postprocess()[effect - 1](setup, x, y)));
//			}
//	}
//	mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
//			SCN.img[SCN.effect]->image, 0, 0);
//}
