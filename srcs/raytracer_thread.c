/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:44:42 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/15 17:41:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void multVecMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
	double a, b, c, w;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0] + x[3][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1] + x[3][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2] + x[3][2];
	w = src->x * x[0][3] + src->y * x[1][3] + src->z * x[2][3] + x[3][3];

	dst->x = a / w;
	dst->y = b / w;
	dst->z = c / w;
}

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
	multVecMatrix(&SETUP.orig, &SETUP.ray.orig, SETUP.camToWorld);
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
	(SCN != NULL) ? mlx_destroy_image(MLX->mlx_ptr, SCN->image) : 0;
	SCN = ft_imgnew(MLX->mlx_ptr, S_WIDTH[WIN], S_HEIGHT[WIN]);
	i = -1;
	while (++i < THREAD)
		pthread_create(&(SETUP.thrd[i]), NULL, ft_raytracing, (void *)setup);
	i = -1;
	while (++i < THREAD)
		pthread_join(SETUP.thrd[i], NULL);
	return (SETUP.error);
}


//void	*trace_thread(void *dt)
//{
//	t_3di		p1;
//	t_3di		col;
//	pthread_t	id;
//	t_data		*d;
//	int			i;
//
//	d = (t_data*)dt;
//	i = -1;
//	id = pthread_self();
//	while (++i < THRD_N)
//		if (pthread_equal(id, d->pth[i]))
//			break ;
//	p1.y = (i * YS) / THRD_N - 1;
//	while (++p1.y < ((i + 1) * YS) / THRD_N && (p1.x = -1))
//		while (++p1.x < XS)
//		{
//			col = trace_one(d, (v_dvop(v_dsop(d->ox, (p1.x - XS / 2), '*')
//				, v_dsop(d->oy, (p1.y - YS / 2), '*'), '+')), -1, -1);
//			draw_pixel(d, p1.x, p1.y, (col.x << 16) + (col.y << 8) + col.z);
//		}
//	pthread_exit(NULL);
//}