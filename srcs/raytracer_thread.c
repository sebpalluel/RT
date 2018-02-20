/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 17:15:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t		ft_initcamToWorld(t_setup *setup)
{
	if (!setup->camToWorld && (setup->camToWorld = ft_matrixzero(4)))
	{
		setup->camToWorld[0][0] = 0.945519;
		setup->camToWorld[0][1] = 0;
		setup->camToWorld[0][2] = -0.125569;
		setup->camToWorld[0][3] = 0;
		setup->camToWorld[1][0] = -0.179534;
		setup->camToWorld[1][1] = 0.834209;
		setup->camToWorld[1][2] = -0.521403;
		setup->camToWorld[1][3] = 0;
		setup->camToWorld[2][0] = 0.271593;
		setup->camToWorld[2][1] = 0.551447;
		setup->camToWorld[2][2] = 0.78876;
		setup->camToWorld[2][3] = 0;
		setup->camToWorld[3][0] = 4.208271;
		setup->camToWorld[3][1] = 8.374532;
		setup->camToWorld[3][2] = 17.932925;
		setup->camToWorld[3][3] = 1;
		return (OK);
	}
	if (setup->camToWorld)
		return (OK);
	return (ERROR);
}

int			ft_raytracing_thread(t_setup *setup)
{
	int		i;
	t_list *list;

	list = SCN.forms;
	printf("sphere r %f\n", SPHERE(list).mat.col.r);
	if (ft_initcamToWorld(setup) != OK)
		return (setup->error = ERROR);
	i = -1;
	while (++i < THREAD)
		pthread_create(&(setup->thrd[i]), NULL, ft_raytracing, (void *)setup);
	i = -1;
	while (++i < THREAD)
		pthread_join(setup->thrd[i], NULL);
	return (setup->error); // Here return OK or the corresponding error
}
