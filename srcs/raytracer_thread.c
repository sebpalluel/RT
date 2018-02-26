/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 13:22:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_raytracing_thread(t_setup *setup)
{
	int			i;
	t_list		*list;
	t_cam		*cam;
	size_t		cam_n;

	list = SCN.cams;
	cam_n = 0;
	while (list && ++cam_n <= SCN.cam_n)
		list = list->next;
	cam = CAM(list);
	ft_look_at(setup, cam);
	i = -1;
	while (++i < THREAD)
		pthread_create(&(setup->thrd[i]), NULL, ft_raytracing, (void *)cam);
	i = -1;
	while (++i < THREAD)
		pthread_join(setup->thrd[i], NULL);
	return (setup->error);
}

size_t			ft_get_thread_n(t_setup *setup)
{
	int			thread_n;
	pthread_t	id;

	id = pthread_self();
	thread_n = -1;
	while (++thread_n < THREAD)
		if (pthread_equal(id, setup->thrd[thread_n]))
			break ;
	return (thread_n);
}
