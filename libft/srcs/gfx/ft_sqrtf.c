/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:11:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/01/31 16:30:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

float	ft_sqrtf(float n)
{
	float ret;
	float precision;

	ret = 1.;
	precision = 0.0000001;
	while (ABS((ret * ret) / n - 1.) >= precision)
		ret -= (ret * ret - n) / (2. * ret);
	return (ret);
}
