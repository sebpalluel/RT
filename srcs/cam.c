/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:49:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			init_cam(t_cam *cam)
{
	cam->frt = ft_vec3normalize_r(ft_vec3vop_r(cam->look_at, cam->org, '-'));
	cam->dwn = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(0., 1., 0.), \
				cam->frt, 'c'));
	if (ft_vec3multscale(cam->dwn, ft_vec3_r(0.0, 0.0, 1.0)) > 0.0)
		cam->dwn = ft_vec3scale(cam->dwn, -1.);
	if (ft_vec3norm(cam->dwn) == 0.0)
	{
		cam->dwn = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(1.0, 0.0, 0.0), \
					cam->frt, 'c'));
		if (ft_vec3multscale(cam->dwn, ft_vec3_r(0.0, 0.0, 1.0)) > 0.0)
			cam->dwn = ft_vec3scale(cam->dwn, -1.);
	}
	cam->rgt = ft_vec3normalize_r(ft_vec3vop_r(cam->frt, cam->dwn, 'c'));
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
	init_cam(CAM(cam));
	SCN.num_cam++;
	*list = env;
	return (OK);
}
