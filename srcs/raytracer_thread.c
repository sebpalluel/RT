/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 17:15:20 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_raytracing_thread(t_setup *setup)
{
	int		i;

	i = -1;
	while (++i < THREAD)
		pthread_create(&(setup->thrd[i]), NULL, ft_raytracing, (void *)setup);
	i = -1;
	while (++i < THREAD)
		pthread_join(setup->thrd[i], NULL);
	return (setup->error); // Here return OK or the corresponding error
}
