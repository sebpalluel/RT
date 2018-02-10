/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invsqrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:19:57 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 17:33:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double				ft_invsqrt(double number)
{
	long long		i;
	double			x2;
	double			y;
	const double	threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long long*)&y;
	i = 0x5fe6ec85e7de30daLL - (i >> 1);
	y = *(double*)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	y = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed
	return (y);
}
