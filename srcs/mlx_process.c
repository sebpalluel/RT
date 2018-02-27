/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:01:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 19:37:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_put_pixel(t_setup *setup, int x, int y, int color)
{
	int			*tmp;
	size_t		index;

	if (y >= (int)SCN.height || x >= (int)SCN.width || x < 0 || y < 0)
		return ;
	index = (y * SCN.width) * (SCN.img->bbp >> 3) \
			+ x * (SCN.img->bbp >> 3);
	tmp = (int *)&SCN.img->image_addr[index];
	*tmp = color;
}

int				ft_expose(t_setup *setup)
{
	int			ret;

	ret = OK;
	ft_imgclean(UI_IMG, setup->width, setup->height);
	if (setup->mode != STATE_STOP && setup->num_scn)
		ft_imgclean(SCN.img, SCN.width, SCN.height);
	if (ret == OK && setup->mode == STATE_DRAW)
	{
		if ((ret = ft_raytracing_thread(setup)) != OK)
			setup->error = ENG_ERROR;
		mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
				SCN.img->image, 0, 0);
		setup->mode = STATE_STOP;
	}
	ft_mlx_control_key(setup);
	if (ret != OK)
		ft_quit(setup);
	return (0);
}

static int		ft_key_hook(int keycode, t_setup *setup)
{
	int			ret;

	setup->key = keycode;
	ret = OK;
	ft_mlx_control_key(setup);
	if (setup->key == ENTER && setup->mode == STATE_START)
		setup->mode = (setup->ac > 1) ? STATE_OPEN : STATE_SELECT;
	if (setup->mode == STATE_SELECT)
		ret = ft_setup_menu(setup);
	if (setup->mode == STATE_OPEN)
		ret = ft_open_scene(setup);
	if (setup->key == ESC || ret != OK)
		ft_quit(setup);
	ft_expose(setup);
	return (0);
}

void			ft_mlx_process(t_setup *setup)
{
	if (setup->mode == STATE_START)
		ft_start(setup);
	mlx_hook(UI_WIN->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hook, setup);
	mlx_hook(UI_WIN->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, \
			ft_quit, setup);
	mlx_expose_hook(UI_WIN->win_ptr, ft_expose, setup);
	mlx_loop(setup->mlx_ptr);
}
