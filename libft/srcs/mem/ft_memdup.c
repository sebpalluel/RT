/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 18:18:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/20 12:24:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memdup(const void *mem, size_t size)
{
	void	*out;

	out = (void*)malloc(size);
	ft_bzero(out, size);
	if (out != NULL)
		ft_memcpy(out, mem, size);
	return (out);
}
