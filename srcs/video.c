/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 21:54:20 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 22:00:35 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_loop_hook(t_setup *setup)
{
	t_vec3	rot;
	double	distance;
	double step;

	if (SCN.cams)
	{
		step = M_PI / 360;
		distance = 1.;
		rot.x = sinf(g_time * step);
		rot.y = cosf(g_time * step);
		rot.z = 0.;
		SCN.cur_cam->org = rot;
		ft_saveimg(SCN, ft_savename("captures/test", g_time));
		setup->mode = STATE_DRAW;
		ft_expose(setup);
		g_time += 1;
	}
	return (0);
}
