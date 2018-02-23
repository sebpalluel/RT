/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 15:58:56 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_look_at(t_setup *setup, t_cam *cam)
{
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;

	forward = ft_vec3normalize_r(ft_vec3vop_r(cam->org, cam->look_at, '-'));
	right = ft_vec3vop_r(ft_vec3normalize_r(ft_vec3_r(0, 1, 0)), forward, 'c');
	up = ft_vec3vop_r(forward, right, 'c');
	setup->camToWorld[0][0] = right.x;
	setup->camToWorld[0][1] = right.y;
	setup->camToWorld[0][2] = right.z;
	setup->camToWorld[1][0] = up.x;
	setup->camToWorld[1][1] = up.y;
	setup->camToWorld[1][2] = up.z;
	setup->camToWorld[2][0] = forward.x;
	setup->camToWorld[2][1] = forward.y;
	setup->camToWorld[2][2] = forward.z;
	setup->camToWorld[3][0] = cam->org.x;
	setup->camToWorld[3][1] = cam->org.y;
	setup->camToWorld[3][2] = cam->org.z;
	setup->camToWorld[3][3] = 1.;
}

void			init_cam(t_cam *cam, t_vec3 org, t_vec3 look_at)
{
	cam->org = org;
	cam->frt = normal_vect(vect_sub(look_at, org));
	cam->dwn = normal_vect(vect_mult(init_vec3(0.0, 1.0, 0.0), cam->frt));
	if (vect_mult_scale(cam->dwn, init_vec3(0.0, 0.0, 1.0)) > 0.0)
		cam->dwn = vect_scale(-1.0, cam->dwn);
	if (norme_vect(cam->dwn) == 0.0)
	{
		cam->dwn = normal_vect(vect_mult(init_vec3(1.0, 0.0, 0.0), cam->frt));
		if (vect_mult_scale(cam->dwn, init_vec3(0.0, 0.0, 1.0)) > 0.0)
			cam->dwn = vect_scale(-1.0, cam->dwn);
	}
	cam->rgt = normal_vect(vect_mult(cam->frt, cam->dwn));
}

static t_list	*ft_newcam(void)
{
	t_list		*cam;

	if (!(cam = (t_list*)malloc(sizeof(t_list))) || \
			!(cam->content = (t_cam*)ft_memalloc(sizeof(t_cam))))
		return (NULL);
	cam->content_size = sizeof(t_cam);
	cam->next = NULL;
	return (cam);
}

static void		ft_cam_struct_pop(t_list *cam, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CAM(cam)->org, ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "look_at") == 0)
		flag[1] = ft_getvectfromenv(&CAM(cam)->look_at, ENVSTRUCT(env)->value);
	CAM(cam)->num_arg++;
}

size_t			ft_cam(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*cam;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCAM)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCAM);
	ft_lstaddend(&SCN.cams, ft_newcam());
	cam = SCN.cams;
	while (cam->next)
		cam = cam->next;
	while (CAM(cam)->num_arg < NVARCAM && env && (env = env->next))
		ft_cam_struct_pop(cam, env, flag);
	if (ft_checkifallset(flag, NVARCAM) != OK)
		return (setup->error = CAM_ERROR);
	SCN.num_cam++;
	*list = env;
	return (OK);
}
