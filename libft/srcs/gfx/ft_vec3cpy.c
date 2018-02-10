/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 22:12:50 by psebasti          #+#    #+#             */
/*   Updated: 2017/07/13 22:15:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vec3cpy(t_vec3 *vec_from, t_vec3 *vec_to)
{
	if (vec_from && vec_to)
	{
		vec_to->x = vec_from->x;
		vec_to->y = vec_from->y;
		vec_to->z = vec_from->z;
	}
}
