/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 11:44:26 by psebasti         ###   ########.fr       */
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
	setup->camtoworld[0][0] = right.x;
	setup->camtoworld[0][1] = right.y;
	setup->camtoworld[0][2] = right.z;
	setup->camtoworld[1][0] = up.x;
	setup->camtoworld[1][1] = up.y;
	setup->camtoworld[1][2] = up.z;
	setup->camtoworld[2][0] = forward.x;
	setup->camtoworld[2][1] = forward.y;
	setup->camtoworld[2][2] = forward.z;
	setup->camtoworld[3][0] = cam->org.x;
	setup->camtoworld[3][1] = cam->org.y;
	setup->camtoworld[3][2] = cam->org.z;
	setup->camtoworld[3][3] = 1.;
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
	if (ft_strcmp(ENV(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CAM(cam)->org, ENV(env)->value);
	else if (ft_strcmp(ENV(env)->name, "look_at") == 0)
		flag[1] = ft_getvectfromenv(&CAM(cam)->look_at, ENV(env)->value);
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
