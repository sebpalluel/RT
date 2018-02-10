/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:34:57 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/12 16:33:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *tofind, size_t n)
{
	size_t	begin;
	size_t	current;

	begin = 0;
	current = 0;
	if (!*tofind)
		return ((char *)str);
	while (str[begin] && n > begin)
	{
		if ((str[begin + current] == tofind[current]) && (begin + current < n))
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
