/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:19:33 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 16:35:08 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_change_cam(t_setup *setup)
{
	int		x;
	char	*nbr;
	int		ret;

	x = setup->width / 32;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x0000FF, \
			CAM_AV_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 290, \
			16, 0x0000FF, nbr = (ft_itoa((int)(SCN.num_cam))));
	free(nbr);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 32, 0x0000FF, \
			CAM_CH_STR);
	ret = ft_mlx_keytoint(setup->key);
	if (ret >= 0 && ret < (int)SCN.num_cam)
	{
		SCN.cam_n = ret;
		mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 445, 32, 0x00FF00, \
				nbr = ft_itoa(ret));
		free(nbr);
		setup->mode = STATE_CAM;
	}
	setup->mode = (setup->mode == STATE_CAM && setup->key == ENTER) ? \
				STATE_DRAW : STATE_CAM;
}

void		ft_mlx_control_key(t_setup *setup)
{
	if (setup->mode == STATE_STOP)
		ft_mlx_control(setup);
	if (setup->key == C_KEY || setup->mode == STATE_CAM)
		ft_change_cam(setup);
	if (setup->key == S_KEY)
		setup->mode = STATE_SELECT;
}

void		ft_mlx_control(t_setup *setup)
{
	int		x;

	x = setup->width / 3;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, UI_IMG->image, \
			0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x0000FF, \
			GUI_M_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 48, 0x0000FF, \
			GUI_M_SCN_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 64, 0x0000FF, \
			GUI_M_CAM_STR);
}
