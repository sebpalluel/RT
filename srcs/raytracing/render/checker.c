/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:02:28 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 22:03:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double			ft_checker(t_vec3 vec3, t_gen gen)
{
	int			size;

	(void)gen;
	size = 5;
	vec3 = ft_vec3multscale_r(vec3, 100.);
	if (((int)floor(vec3.x / size)
				+ (int)floor(vec3.y / size)) % 2 != 0)
		return (1.);
	else
		return (0.);
}
