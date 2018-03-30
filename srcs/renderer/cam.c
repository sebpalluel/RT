/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 17:54:35 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

void			init_cam(t_cam *cam)
{
	cam->frt = ft_vec3normalize_r(ft_vec3vop_r(cam->look_at, cam->org, '-'));
	cam->dwn = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(0., 1., 0.), \
				cam->frt, 'c'));
	if (ft_vec3dot(cam->dwn, ft_vec3_r(0.0, 0.0, 1.0)) > 0.0)
		cam->dwn = ft_vec3multscale_r(cam->dwn, -1.);
	if (ft_vec3norm(cam->dwn) == 0.0)
	{
		cam->dwn = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(1.0, 0.0, 0.0), \
					cam->frt, 'c'));
		if (ft_vec3dot(cam->dwn, ft_vec3_r(0.0, 0.0, 1.0)) > 0.0)
			cam->dwn = ft_vec3multscale_r(cam->dwn, -1.);
	}
	cam->rgt = ft_vec3normalize_r(ft_vec3vop_r(cam->frt, cam->dwn, 'c'));
}

void			ft_cam_change(t_setup *setup)
{
	t_list		*list;
	size_t		cam_n;

	list = SCN.cams;
	cam_n = 0;
	SCN.cur_cam = CAM(list);
	if (SCN.cam_n < SCN.num_cam)
		while (list && ++cam_n <= SCN.cam_n)
			list = list->next;
	SCN.cur_cam = CAM(list);
}
