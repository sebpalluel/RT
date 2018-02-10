/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:46:07 by psebasti          #+#    #+#             */
/*   Updated: 2017/09/07 20:19:43 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*str_set;
	size_t			i;

	i = 0;
	if (!n)
		return (str);
	else
		str_set = (unsigned char *)str;
	while (i < n)
	{
		str_set[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
