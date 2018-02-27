/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:37:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:41:31 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3			ft_vec3normalize_r(t_vec3 from_vec3)
{
	double		n;

	n = ft_vec3norm(from_vec3);
	if (n <= 0.0)
		return (ft_vec3_r(0.0, 0.0, 0.0));
	from_vec3.x = from_vec3.x / n;
	from_vec3.y = from_vec3.y / n;
	from_vec3.z = from_vec3.z / n;
	return (from_vec3);
}
