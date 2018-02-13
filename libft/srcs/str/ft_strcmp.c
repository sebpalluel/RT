/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:27:51 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/13 16:55:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

size_t		ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
