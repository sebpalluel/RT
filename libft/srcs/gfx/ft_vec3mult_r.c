/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3mult_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:48:47 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/07 13:20:57 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3mult_r(t_vec3 a, t_vec3 b)
{
	t_vec3	to_vec3;

	to_vec3.x = a.x * b.x;
	to_vec3.y = a.y * b.y;
	to_vec3.z = a.z * b.z;
	return (to_vec3);
}
