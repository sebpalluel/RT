/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:33:52 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/12 00:43:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(dest);
	if (dest || src)
	{
		while (src[i] && i < n)
		{
			dest[length + i] = src[i];
			i++;
		}
		dest[length + i] = '\0';
		return (dest);
	}
	return (NULL);
}
