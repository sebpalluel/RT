/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:01:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/12 14:23:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_expose(t_setup *setup)
{
	int		ret;

	ret = OK;
	ft_imgclean(IMG, SETUP.width, SETUP.height);
	if (ret == OK && SETUP.mode == STATE_DRAW) // on rentre dans la fonction de raytracing
	{
		if ((ret = ft_raytracing(setup)) == ERROR)
			SETUP.error = MAP_ERROR;
		mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG->image, 0, 0);
	}
		//if (!SETUP.ui)
			ft_mlx_control_key(setup);
	if (ret != OK)
		ft_setup_mode(&SETUP, 0);
	return (0);
}

static int	ft_key_hook(int keycode, t_setup *setup)
{
	int		ret;

	SETUP.key = keycode;
	ret = OK; // je part du principe que tout est OK pour detecter erreur eventuelle
	if (SETUP.key == ENTER && SETUP.mode == STATE_START)
		SETUP.mode = (SETUP.ac > 1) ? STATE_OPEN : STATE_SELECT; // Si arg va direct lancer parsing de la map sinon selection de map
	if (SETUP.mode == STATE_SELECT)
		ret = ft_setup_menu(setup); // menu de selection de map
	if (SETUP.mode == STATE_OPEN)
		ret = ft_open_map(setup); // va ouvrir la map selon le path
	if (SETUP.key == ESC || ret != OK) // le ret va permettre de savoir si il y a eu une erreur de parsing et dans ce cas exit et free
		ft_quit(setup); // on sera si il y a erreur laquelle
	ft_mlx_control_key(&SETUP);
	ft_expose(setup);
	mlx_do_sync(MLX->mlx_ptr);
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
	mlx_hook(MLX->win_ptr, KEYPRESS, KEYPRESSMASK, ft_key_hook, setup);
	mlx_hook(MLX->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, setup);
	mlx_expose_hook(MLX->win_ptr, ft_expose, setup);
	mlx_loop(MLX->mlx_ptr);
}
