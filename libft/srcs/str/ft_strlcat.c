/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:17:27 by psebasti          #+#    #+#             */
/*   Updated: 2016/12/17 16:16:27 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (dst[i] && i < size)
		i++;
	len = i;
	while (src[i - len] && (i + 1) < size)
	{
		dst[i] = src[i - len];
		i++;
	}
	if (size > len)
		dst[i] = '\0';
	return (len + ft_strlen(src));
}
