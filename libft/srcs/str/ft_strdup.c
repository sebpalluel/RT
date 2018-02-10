/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:14:44 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/17 16:28:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	length;

	length = ft_strlen(src) + 1;
	if (!(dest = (char*)ft_memalloc(length)))
		return (NULL);
	ft_memcpy((void*)dest, (void*)src, length);
	return (dest);
}
