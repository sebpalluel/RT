/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3unit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:53:47 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 17:34:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3				ft_vec3unit(t_vec3 from)
{
	double			is;

	is = ft_invsqrt(SQUARE(from.x) + SQUARE(from.y) + SQUARE(from.z));
	return (ft_vec3sop_r(from, is, '*'));
}
