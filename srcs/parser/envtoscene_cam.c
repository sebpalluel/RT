/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 17:52:59 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 18:03:24 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

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

static void		ft_cam_struct_pop(t_list *cam, t_list *env, t_bool *flag, \
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CAM(cam)->org, P_ENV(env)->value);
	else if (ft_strcmp(P_ENV(env)->name, "look_at") == 0)
		flag[1] = ft_getvectfromenv(&CAM(cam)->look_at, P_ENV(env)->value);
	*num_arg += 1;
}

size_t			ft_cam(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*cam;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCAM)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCAM);
	ft_lstaddend(&scn->cams, ft_newcam());
	cam = scn->cams;
	num_arg = 0;
	while (cam->next)
		cam = cam->next;
	while (num_arg < NVARCAM && env && (env = env->next))
		ft_cam_struct_pop(cam, env, flag, &num_arg);
	if (ft_checkifallset(flag, NVARCAM) != OK)
		return (scn->error = CAM_ERROR);
	init_cam(CAM(cam));
	scn->num_cam++;
	*list = env;
	return (OK);
}


