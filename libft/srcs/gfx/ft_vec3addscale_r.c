/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3addscale_r.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:40:09 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 16:41:24 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3	ft_vec3addscale_r(t_vec3 v, double a)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}