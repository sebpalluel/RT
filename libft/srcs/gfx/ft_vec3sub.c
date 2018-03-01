/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3sub_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:29:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 16:45:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3sub_r(t_vec3 a, t_vec3 b)
{
	t_vec3	to_vec3;

	ft_bzero(&to_vec3, sizeof(t_vec3));
		to_vec3.x = a.x - b.x;
		to_vec3.y = a.y - b.y;
		to_vec3.z = a.z - b.z;
	return (to_vec3);
}
