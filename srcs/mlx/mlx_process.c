/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:01:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/04 20:57:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void				ft_getdeltatime(struct timespec start)
{
	double			delta_time;
	struct timespec	end;
	char			*nbr;

	clock_gettime(CLOCK_REALTIME, &end);
	delta_time = (end.tv_sec - start.tv_sec) \
		+ (end.tv_nsec - start.tv_nsec) / 1E9;
	if ((nbr = ft_ftoa(delta_time)))
	{
		ft_putstr(nbr);
		ft_putendl(" sec");
		free(nbr);
	}
}

int					ft_expose(t_setup *setup)
{
	int				ret;
	struct timespec	start;

	ret = OK;
	ft_imgclean(UI_IMG, setup->width, setup->height);
	if (ret == OK && setup->mode == STATE_DRAW)
	{
		ft_imgclean(SCN.img[0], SCN.width, SCN.height);
		mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
				setup->loading->image, SCN.width / 3., SCN.height / 2.7);
		clock_gettime(CLOCK_REALTIME, &start);
		if ((ret = ft_raytracing_thread(setup)) != OK)
			setup->error = ENG_ERROR;
		mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
				SCN.img[SCN.effect]->image, 0, 0);
		ft_getdeltatime(start);
		setup->mode = STATE_STOP;
	}
	if (setup->mode == STATE_STOP)
		ft_mlx_control(setup);
	if (ret != OK)
		ft_quit(setup);
	return (0);
}

int					ft_key_hook(int keycode, t_setup *setup)
{
	int				ret;

	setup->key = keycode;
	ret = OK;
	if (setup->mode != STATE_START)
		ft_mlx_control_key(setup);
	if (setup->key == ENTER && setup->mode == STATE_START)
		setup->mode = (setup->ac > 1) ? STATE_OPEN : STATE_SELECT;
	if (setup->mode == STATE_SELECT)
		ret = ft_setup_menu(setup);
	if (setup->mode == STATE_OPEN)
		ret = ft_open_scene(setup);
	if (ret != OK)
		ft_quit(setup);
	ft_expose(setup);
	return (0);
}

void				ft_mlx_process(t_setup *setup)
{
	if (setup->mode == STATE_START)
		ft_start(setup);
	mlx_hook(UI_WIN->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hook, setup);
	mlx_hook(UI_WIN->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, \
			ft_quit, setup);
	if (VIDEO_MODE)
		mlx_loop_hook(UI_WIN->mlx_ptr, ft_loop_hook, setup);
	mlx_expose_hook(UI_WIN->win_ptr, ft_expose, setup);
	mlx_loop(setup->mlx_ptr);
}
