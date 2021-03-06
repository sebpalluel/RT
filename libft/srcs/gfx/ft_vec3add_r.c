/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3add_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:46:04 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 23:03:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3add_r(t_vec3 a, t_vec3 b)
{
	t_vec3	to_vec3;

	to_vec3.x = a.x + b.x;
	to_vec3.y = a.y + b.y;
	to_vec3.z = a.z + b.z;
	return (to_vec3);
}
