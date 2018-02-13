/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:25:40 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/13 17:31:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lastoccur(int *begin, int *current, size_t *occur_n)
{
	if (!*occur_n)
		return (OK);
	else
	{
		*occur_n -= 1;
		*begin += *current;
		*current = 0;
		return (ERROR);
	}
}

char			*ft_strstrn(const char *str, const char *tofind, size_t occur_n)
{
	int			begin;
	int			current;

	begin = 0;
	current = 0;
	if (!*tofind)
		return ((char *)str);
	while (str && str[begin])
	{
		if (str[begin + current] == tofind[current])
			current++;
		else
		{
			current = 0;
			begin++;
		}
		if (!tofind[current])
		{
			if (ft_lastoccur(&begin, &current, &occur_n) == OK)
				return ((char *)str + begin);
		}
	}
	return (NULL);
}
