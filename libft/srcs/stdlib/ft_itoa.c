/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:21:03 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/22 18:16:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_isnegative(int *n, int *negative)
{
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
	}
}

char			*ft_itoa(int n)
{
	int				tmpn;
	unsigned int	len;
	int				negative;
	char			*str;

	tmpn = n;
	len = 1;
	negative = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_isnegative(&n, &negative);
	while (tmpn /= 10)
		len++;
	len += negative;
	if (!(str = ft_memalloc(len + 1)))
		return (NULL);
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
