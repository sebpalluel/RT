/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:33:26 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 20:37:54 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_cam_select(t_setup *setup)
{
	int		x;
	char	*nbr;
	int		ret;

	x = setup->width / 32;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x32cd32, \
			CAM_AV_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 290, \
			16, 0x32cd32, nbr = (ft_itoa((int)(SCN.num_cam))));
	free(nbr);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 32, 0x32cd32, \
			CAM_CH_STR);
	if ((ret = ft_mlx_keytoint(setup->key)) >= 0 && ret < (int)SCN.num_cam)
	{
		SCN.cam_n = ret;
		mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 445, 32, 0x00FF00, \
				nbr = ft_itoa(ret));
		free(nbr);
		setup->mode = STATE_CAM;
		ft_cam_change(setup);
	}
	setup->mode = (setup->mode == STATE_CAM && setup->key == ENTER) ? \
				  STATE_DRAW : STATE_CAM;
}

void		ft_effect_select(t_setup *setup)
{
	int		x;
	char	*nbr;
	int		ret;

	x = setup->width / 32;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x32cd32, \
			EFF_AV_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 32, 0x32cd32, \
			EFF_CH_STR);
	ret = ft_mlx_keytoint(setup->key);
	if (ret >= 0 && ret <= NUM_EFFECTS)
	{
		mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 490, 32, 0x00FF00, \
				nbr = ft_itoa(ret));
		free(nbr);
		setup->mode = STATE_EFF;
		ft_effect_change(setup, ret);
	}
	setup->mode = (setup->mode == STATE_EFF && setup->key == ENTER) ? \
				  STATE_STOP : STATE_EFF;
}

void		ft_take_screenshot(t_setup *setup)
{
	int		x;
	char	*nbr;
	int		ret;

	x = setup->width / 32;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 32, 0x32cd32, \
			WRI_CH_STR);
	ret = ft_mlx_keytoint(setup->key);
	if (ret >= 0 && ret <= NUM_EFFECTS)
	{
		mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 490, 32, 0x00FF00, \
				nbr = ft_itoa(ret));
		free(nbr);
		setup->mode = STATE_WRI;
		g_time = ret;
	}
	if (setup->mode == STATE_WRI && setup->key == ENTER)
	{
		ft_saveimg(SCN, ft_savename("captures/screenshot_", g_time));
		setup->mode = STATE_STOP;
	}
	else
		setup->mode = STATE_WRI;
}
