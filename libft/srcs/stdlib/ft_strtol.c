/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:02:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/03 12:27:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int				ft_strtol(const char *str, int base)
{
	char				*tmp;
	unsigned long		n;

	tmp = (char *)str;
	while (ft_isspace(*tmp) == OK)
		tmp++;
	n = ft_stoul(str, base);
	if (*tmp == '-' && n <= LONG_MAX)
		return (LONG_MIN);
	else if (*tmp != '-' && LONG_MAX < n)
		return (LONG_MAX);
	else
		return ((long)n);
}
