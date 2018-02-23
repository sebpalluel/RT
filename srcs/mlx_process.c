/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:01:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 10:51:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_expose(t_setup *setup)
{
	int		ret;
	float	delta_time;
	float	begin_time;

	ret = OK;
	ft_imgclean(UI_IMG, setup->width, setup->height);
	//TODO adapt here for scene
	if (setup->mode != STATE_STOP && setup->num_scn)
		ft_imgclean(SCN.img, SCN.width, SCN.height);
	if (ret == OK && setup->mode == STATE_DRAW) // on rentre dans la fonction de raytracing
	{
		begin_time = clock();
		if ((ret = ft_raytracing_thread(setup)) != OK)
			setup->error = ENG_ERROR;
	//TODO adapt here for scene
		mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, SCN.img->image, 0, 0);
		setup->mode = STATE_STOP;
		delta_time = (float)(clock() - begin_time) / CLOCKS_PER_SEC;
		printf("drawn in %f sec\n", delta_time);
	}
	//if (!setup->ui)
	ft_mlx_control_key(setup);
	if (ret != OK)
		ft_quit(setup);
	return (0);
}

static int	ft_key_hook(int keycode, t_setup *setup)
{
	int		ret;

	setup->key = keycode;
	ret = OK; // je part du principe que tout est OK pour detecter erreur eventuelle
	ft_mlx_control_key(setup);
	if (setup->key == ENTER && setup->mode == STATE_START)
		setup->mode = (setup->ac > 1) ? STATE_OPEN : STATE_SELECT; // Si arg va direct lancer parsing de la map sinon selection de map
	if (setup->mode == STATE_SELECT)
		ret = ft_setup_menu(setup); // menu de selection de map
	if (setup->mode == STATE_OPEN)
		ret = ft_open_scene(setup); // va ouvrir la map selon le path
	if (setup->key == ESC || ret != OK) // le ret va permettre de savoir si il y a eu une erreur de parsing et dans ce cas exit et free
		ft_quit(setup); // on sera si il y a erreur laquelle
	ft_expose(setup);
	return (0);
}

void		ft_mlx_process(t_setup *setup)
{
	if (setup->mode == STATE_START)
		ft_start(setup); // juste UI, taper ENTER
	mlx_hook(UI_WIN->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hook, setup);
	mlx_hook(UI_WIN->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, \
			ft_quit, setup);
	mlx_expose_hook(UI_WIN->win_ptr, ft_expose, setup);
	mlx_loop(setup->mlx_ptr);
}
