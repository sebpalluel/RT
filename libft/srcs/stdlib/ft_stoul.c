/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:04:31 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/11 16:26:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			pos(int c, int base)
{
	char			*hex;
	int				i;

	hex = "0123456789abcdef";
	i = 0;
	while (i < base)
	{
		if (hex[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int			lenght(char *str, int base)
{
	int				i;

	i = 0;
	while (str[i] && (pos(ft_tolower(str[i]), base) != -1))
		i++;
	return (i);
}

unsigned long		ft_stoul(const char *str, int base)
{
	unsigned long	n;
	char			sign;
	int				len;

	if (base < 0 || base == 1 || base > 16 || !(base))
		return (0);
	while (ft_isspace(*str) == OK)
		str++;
	sign = (*str == '-' || *str == '+') ? *str++ : '+';
	while (*str == '0')
		str++;
	len = lenght((char *)str, base) - 1;
	n = 0;
	while (len >= 0)
	{
		n = n + (pos(ft_tolower(*str), base) * ft_pow(base, len));
		len--;
		str++;
	}
	return (sign == '-' && base == 10 ? -n : n);
}
