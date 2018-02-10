/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:55:30 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/12 15:03:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_range_num(double input, double i[2], double o[2])
{
	double	slope;
	double	output;

	slope = 1.0 * (o[1] - o[0]) / (i[1] - i[0]);
	output = o[0] + slope * (input - i[0]);
	return (output);
}
