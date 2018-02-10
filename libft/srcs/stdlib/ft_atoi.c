/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 19:12:47 by psebasti          #+#    #+#             */
/*   Updated: 2018/01/19 18:27:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]) == OK)
		i++;
	if (str[i] == '-')
	{
		sign = 0;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == OK)
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign ? nb : -nb);
}
