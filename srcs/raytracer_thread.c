/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 15:06:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t		ft_initcamToWorld(t_setup *setup)
{
	if (!SETUP.camToWorld && (SETUP.camToWorld = ft_matrixzero(4)))
	{
		SETUP.camToWorld[0][0] = 0.945519;
		SETUP.camToWorld[0][1] = 0;
		SETUP.camToWorld[0][2] = -0.125569;
		SETUP.camToWorld[0][3] = 0;
		SETUP.camToWorld[1][0] = -0.179534;
		SETUP.camToWorld[1][1] = 0.834209;
		SETUP.camToWorld[1][2] = -0.521403;
		SETUP.camToWorld[1][3] = 0;
		SETUP.camToWorld[2][0] = 0.271593;
		SETUP.camToWorld[2][1] = 0.551447;
		SETUP.camToWorld[2][2] = 0.78876;
		SETUP.camToWorld[2][3] = 0;
		SETUP.camToWorld[3][0] = 4.208271;
		SETUP.camToWorld[3][1] = 8.374532;
		SETUP.camToWorld[3][2] = 17.932925;
		SETUP.camToWorld[3][3] = 1;
		return (OK);
	}
	if (SETUP.camToWorld)
		return (OK);
	return (ERROR);
}

int			ft_raytracing_thread(t_setup *setup)
{
	int		i;

	if (ft_initcamToWorld(setup) != OK)
		return (SETUP.error = ERROR);
	i = -1;
	while (++i < THREAD)
		pthread_create(&(SETUP.thrd[i]), NULL, ft_raytracing, (void *)setup);
	i = -1;
	while (++i < THREAD)
		pthread_join(SETUP.thrd[i], NULL);
	return (SETUP.error); // Here return OK or the corresponding error
}
