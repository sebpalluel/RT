/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:19:33 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 19:22:49 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//void		ft_modify_speed(t_setup *setup)
//{
//	if (setup->key == EQUAL && setup->move_step <= 0.8)
//	{
//		setup->rot_step += 0.05;
//		setup->move_step += 0.05;
//	}
//	if (setup->key == MINUS && setup->move_step >= 0.1)
//	{
//		setup->rot_step -= 0.05;
//		setup->move_step -= 0.05;
//	}
//}
//
void		ft_change_cam(t_setup *setup)
{
	int		x;
	char	*nbr;

	OK;
	x = setup->width / 32;
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x0000FF, CAM_AV_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x + 290, \
			16, 0x0000FF, nbr = (ft_itoa((int)(SCN.num_cam))));
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 32, 0x0000FF, CAM_CH_STR);

}

void		ft_mlx_control_key(t_setup *setup)
{
	if (setup->mode == STATE_STOP)
		ft_mlx_control(setup);
	if (setup->key == C_KEY || setup->mode == STATE_CAM)
		ft_change_cam(setup);
	if (setup->key == S_KEY)
		setup->mode = STATE_SELECT; // va ouvrir la map selon le path
	//if (setup->key == DOWN)
	//	setup->udlr[1] = 1;
	//if (setup->key == LEFT)
	//	setup->udlr[2] = 1;
	//if (setup->key == RIGHT)
	//	setup->udlr[3] = 1;
	//if (setup->key == G_KEY)
	//	setup->ui = !setup->ui ? 1 : 0;
	//if (setup->key == C_KEY)
	//	MAP->cheat = !MAP->cheat ? 1 : 0;
	//if (setup->key == B_KEY)
	//	MAP->skybox = !MAP->skybox ? 1 : 0;
	//if (setup->key == D_KEY)
	//	MAP->drunk_mode = !MAP->drunk_mode ? 1 : 0;
	//if (setup->key == M_KEY)
	//	MAP->draw_map = !MAP->draw_map ? 1 : 0;
}

void		ft_mlx_control(t_setup *setup)
{
	int		x;

	x = setup->width / 3;
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 16, 0x0000FF, \
			GUI_M_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 48, 0x0000FF, \
			GUI_M_SCN_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 48, 0x0000FF, LEFT_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 64, 0x0000FF, RIGHT_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 80, 0xccffff, PLUS_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 96, 0xccffff, MINUS_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 112, 0xccffee, DRUNK_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 128, 0xccccff, MAP_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 144, 0xccccff, GUI_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 160, 0xccccff, SKY_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 176, 0xccccff, CHEAT_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 192, 0xffffff, S_MODE_STR);
	//mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, x, 208, 0xFFcccc, ESC_STR);
}
