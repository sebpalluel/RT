/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3sop_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 13:19:15 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 18:28:11 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3sop_r2(t_vec3 to_vec3, t_vec3 from_vec3, double x, char c)
{
	if (c == '=')
	{
		to_vec3.x = x;
		to_vec3.y = x;
		to_vec3.z = x;
	}
	else if (c == '/')
	{
		to_vec3.x = from_vec3.x / x;
		to_vec3.y = from_vec3.y / x;
		to_vec3.z = from_vec3.z / x;
	}
	return (to_vec3);
}

t_vec3		ft_vec3sop_r(t_vec3 from_vec3, double x, char c)
{
	t_vec3	to_vec3;

	ft_bzero(&to_vec3, sizeof(t_vec3));
	if (c == '+')
	{
		to_vec3.x = from_vec3.x + x;
		to_vec3.y = from_vec3.y + x;
		to_vec3.z = from_vec3.z + x;
	}
	else if (c == '*')
	{
		to_vec3.x = from_vec3.x * x;
		to_vec3.y = from_vec3.y * x;
		to_vec3.z = from_vec3.z * x;
	}
	return (ft_vec3sop_r2(to_vec3, from_vec3, x, c));
}
