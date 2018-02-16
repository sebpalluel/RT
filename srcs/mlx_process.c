/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:01:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 13:14:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_expose(t_setup *setup)
{
	int		ret;

	ret = OK;
	ft_imgclean(&IMG[UI], S_WIDTH[UI], S_HEIGHT[UI]);
	//if (SETUP.mode != STATE_STOP && WIN)
	//	ft_imgclean(SCN, S_WIDTH[WIN], S_HEIGHT[WIN]);
	if (ret == OK && SETUP.mode == STATE_DRAW) // on rentre dans la fonction de raytracing
	{
		if ((ret = ft_raytracing_thread(setup)) != OK)
			SETUP.error = ENG_ERROR;
		//mlx_put_image_to_window(SETUP.mlx_ptr, MLX[WIN].win_ptr, \
		//			SCN->image, 0, 0);
		//SETUP.mode = STATE_STOP;
		printf("drawn\n");
	}
	//if (!SETUP.ui)
	ft_mlx_control_key(setup);
	if (ret != OK)
		ft_setup_mode(&SETUP, 0);
	printf("re process\n");
	return (0);
}

static int	ft_key_hook(int keycode, t_setup *setup)
{
	int		ret;

	SETUP.key = keycode;
	printf("key %d\n", keycode);
	ret = OK; // je part du principe que tout est OK pour detecter erreur eventuelle
	if (SETUP.key == ENTER && SETUP.mode == STATE_START)
		SETUP.mode = (SETUP.ac > 1) ? STATE_OPEN : STATE_SELECT; // Si arg va direct lancer parsing de la map sinon selection de map
	if (SETUP.mode == STATE_SELECT)
		ret = ft_setup_menu(setup); // menu de selection de map
	if (SETUP.mode == STATE_OPEN)
		ret = ft_open_scene(setup); // va ouvrir la map selon le path
	if (SETUP.key == ESC || ret != OK) // le ret va permettre de savoir si il y a eu une erreur de parsing et dans ce cas exit et free
		ft_quit(setup); // on sera si il y a erreur laquelle
	ft_mlx_control_key(&SETUP);
	ft_expose(setup);
	return (0);
}

int			ft_quit(t_setup *setup)
{
	ft_setup_mode(&SETUP, 0);
	return (0);
}

void		ft_mlx_process(t_setup *setup)
{
	if (SETUP.mode == STATE_START)
		ft_start(setup); // juste UI, taper ENTER
	mlx_hook(UI_WIN->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hook, setup);
	mlx_hook(UI_WIN->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, \
			ft_quit, setup);
	mlx_expose_hook(UI_WIN->win_ptr, ft_expose, setup);
	mlx_loop(SETUP.mlx_ptr);
}
