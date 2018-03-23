/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/19 16:37:35 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_raytracing_thread(t_setup *setup)
{
	int			i;

	i = -1;
	while (++i < THREAD)
		if (pthread_create(&(setup->thrd[i]), NULL, ft_raytracing, (void *)setup))
			ft_quit(setup);
	i = -1;
	while (++i < THREAD)
		if (pthread_join(setup->thrd[i], NULL))
			ft_quit(setup);
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
