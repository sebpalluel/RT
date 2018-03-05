/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:55:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/05 18:12:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

float		ft_randf()
{
	int		x;

	x = rand();
	x = (x << 13) ^ x;
	return ((float)( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) \
					& 0x7fffffff) / 1073741824.0));
}
