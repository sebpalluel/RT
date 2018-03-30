/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_torus_moebius.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:20:52 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 19:07:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"



//TODO here dummy functions to avoid segfault in raytracer :

t_vec3			normal_tor(t_ray ray, t_list *tor)
{
	(void)ray;
	(void)tor;

	return (ft_vec3_r(0., 0., 0.));
}
