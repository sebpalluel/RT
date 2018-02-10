/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3sop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:04:49 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:56:11 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_vec3sop(t_vec3 *to_vec3, t_vec3 from_vec3, double x, char c)
{
		if (c == '+')
		{
			to_vec3->x = from_vec3.x + x;
			to_vec3->y = from_vec3.y + x;
			to_vec3->z = from_vec3.z + x;
		}
		else if (c == '*')
		{
			to_vec3->x = from_vec3.x * x;
			to_vec3->y = from_vec3.y * x;
			to_vec3->z = from_vec3.z * x;
		}
		else if (c == '/')
		{
			to_vec3->x = from_vec3.x / x;
			to_vec3->y = from_vec3.y / x;
			to_vec3->z = from_vec3.z / x;
		}
		else if (c == '=')
		{
			to_vec3->x = x;
			to_vec3->y = x;
			to_vec3->z = x;
		}
}
