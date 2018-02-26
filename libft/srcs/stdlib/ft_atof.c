/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:15:18 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 17:31:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double			ft_atof(const char *str)
{
	int			i;
	int			x;
	double		sign;
	double		res;

	i = 0;
	x = 0;
	res = 0;
	while (str[i] == ' ')
		i++;
	sign = (str[i] == '-' ? -1 : 1);
	i += ((str[i] == '-' || str[i] == '+') ? 1 : 0);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != '.' && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	i += ((str[i] == '.') ? 1 : 0);
	while (str[i + x] && (str[i + x] >= '0' && str[i + x] <= '9'))
		res = res * 10 + (str[i + x++] - '0');
	while (x-- > 0)
		res /= 10;
	return (res * sign);
}
