/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/15 16:55:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_raytracing_thread(t_setup *setup)
{
	int		i;

i = -1;
	while (++i < THREAD)
		pthread_create(&(SETUP.thrd[i]), NULL, ft_raytracing, (void *)setup);
	i = -1;
	while (++i < THREAD)
		pthread_join(SETUP.thrd[i], NULL);
	return (SETUP.error);
}
