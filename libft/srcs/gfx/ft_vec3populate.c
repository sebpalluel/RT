/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:38:13 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:56:08 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_vec3populate(t_vec3 *to_vec3, double x, double y, double z)
{
	if (to_vec3)
	{
		to_vec3->x = x;
		to_vec3->y = y;
		to_vec3->z = z;
	}
}
