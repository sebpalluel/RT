/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:37:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 11:06:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_vec3normalize(t_vec3 *to_vec3)
{
	double	n;

	if (to_vec3)
	{
		n = ft_vec3norm(*to_vec3);
		if (n != 0.0)
		{
			to_vec3->x /= n;
			to_vec3->y /= n;
			to_vec3->z /= n;
		}
	}
}
