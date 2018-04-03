
#include "../includes/rtv1.h"

#define BLUR_SIZE 5

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
