/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3vop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:11:37 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:57:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_vec3vop2(t_vec3 *to_vec3, t_vec3 a, t_vec3 b, char c)
{
		if (c == '/')
		{
			to_vec3->x = a.x / b.x;
			to_vec3->y = a.y / b.y;
			to_vec3->z = a.z / b.z;
		}
		else if (c == 'c')
		{
			to_vec3->x = a.y * b.z - a.z * b.y;
			to_vec3->y = a.z * b.x - a.x * b.z;
			to_vec3->z = a.x * b.y - a.y * b.x;
		}
}

void	ft_vec3vop(t_vec3 *to_vec3, t_vec3 a, t_vec3 b, char c)
{
		if (c == '+')
		{
			to_vec3->x = a.x + b.x;
			to_vec3->y = a.y + b.y;
			to_vec3->z = a.z + b.z;
		}
		else if (c == '-')
		{
			to_vec3->x = a.x - b.x;
			to_vec3->y = a.y - b.y;
			to_vec3->z = a.z - b.z;
		}
		else if (c == '*')
		{
			to_vec3->x = a.x * b.x;
			to_vec3->y = a.y * b.y;
			to_vec3->z = a.z * b.z;
		}
		ft_vec3vop2(to_vec3, a, b, c);
}
