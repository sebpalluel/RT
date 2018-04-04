/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:19:33 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/04 20:05:28 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_mlx_control(t_setup *setup)
{
	int		x;

	x = setup->width / 3;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, UI_IMG->image, \
			0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x32cd32, \
			GUI_M_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 48, 0x32cd32, \
			GUI_M_SCN_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 64, 0x32cd32, \
			GUI_M_CAM_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 80, 0x32cd32, \
			GUI_M_EFF_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 96, 0x32cd32, \
			GUI_M_SCR_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 118, 0x32cd32, \
			GUI_M_ESC_STR);
}

void		ft_mlx_control_key(t_setup *setup)
{
	if (setup->mode == STATE_STOP)
		ft_mlx_control(setup);
	if (setup->key == C_KEY || setup->mode == STATE_CAM)
		ft_cam_select(setup);
	if (setup->key == S_KEY)
		setup->mode = STATE_SELECT;
	if (setup->key == W_KEY || setup->mode == STATE_WRI)
		ft_take_screenshot(setup);
	if ((setup->key == E_KEY || setup->mode == STATE_EFF) && setup->mode != 
			STATE_START)
		ft_effect_select(setup);
	if (setup->key == ESC)
		ft_quit(setup);
}
