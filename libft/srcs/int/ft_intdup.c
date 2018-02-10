/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:24:03 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 16:24:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*ft_intdup(int *array, size_t width)
{
	int		*dest;
	size_t	i;

	i = 0;
	if (!(dest = (int *)ft_memalloc(width * sizeof(int))))
		return (NULL);
	while (i < width)
	{
		dest[i] = array[i];
		i++;
	}
	return (dest);
}
