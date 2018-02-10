/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 14:58:15 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/18 15:00:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s = ft_strnew(ft_strlen(s1) + (ft_strlen(s2) * len) + 1);
	if (s)
	{
		ft_strcat(s, s1);
		while (i < len)
		{
			ft_strcat(s, s2);
			i++;
		}
	}
	return (s);
}
