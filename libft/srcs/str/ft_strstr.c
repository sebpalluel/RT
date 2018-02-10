/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:36:22 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/12 16:32:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *tofind)
{
	int		begin;
	int		current;

	begin = 0;
	current = 0;
	if (!*tofind)
		return ((char *)str);
	while (str[begin])
	{
		if (str[begin + current] == tofind[current])
			current++;
		else
		{
			current = 0;
			begin++;
		}
		if (!tofind[current])
			return ((char *)str + begin);
	}
	return (NULL);
}
