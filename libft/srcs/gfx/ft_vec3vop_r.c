/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3vop_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 13:25:07 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 18:27:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3vop_r2(t_vec3 to_vec3, t_vec3 a, t_vec3 b, char c)
{
		if (c == '*')
		{
			to_vec3.x = a.x * b.x;
			to_vec3.y = a.y * b.y;
			to_vec3.z = a.z * b.z;
		}
		else if (c == 'c')
		{
			to_vec3.x = a.y * b.z - a.z * b.y;
			to_vec3.y = a.z * b.x - a.x * b.z;
			to_vec3.z = a.x * b.y - a.y * b.x;
		}
		return (to_vec3);
}

t_vec3		ft_vec3vop_r(t_vec3 a, t_vec3 b, char c)
{
	t_vec3	to_vec3;

	ft_bzero(&to_vec3, sizeof(t_vec3));
		if (c == '+')
		{
			to_vec3.x = a.x + b.x;
			to_vec3.y = a.y + b.y;
			to_vec3.z = a.z + b.z;
		}
		else if (c == '-')
		{
			to_vec3.x = a.x - b.x;
			to_vec3.y = a.y - b.y;
			to_vec3.z = a.z - b.z;
		}
		else if (c == '/')
		{
			to_vec3.x = a.x / b.x;
			to_vec3.y = a.y / b.y;
			to_vec3.z = a.z / b.z;
		}
		return (ft_vec3vop_r2(to_vec3, a, b, c));
}
