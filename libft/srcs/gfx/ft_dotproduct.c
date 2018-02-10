/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotproduct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:30:24 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:55:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double		ft_dotproduct(t_vec3 a, t_vec3 b)
{
	double	sum;

	sum = 0.;
	sum += a.x * b.x;
	sum += a.y * b.y;
	sum += a.z * b.z;
	return (sum);
}
