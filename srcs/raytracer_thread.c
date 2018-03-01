/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 15:07:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_raytracing_thread(t_setup *setup)
{
	int			i;

	i = -1;
	while (++i < THREAD)
		pthread_create(&(setup->thrd[i]), NULL, ft_raytracing, (void *)setup);
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
