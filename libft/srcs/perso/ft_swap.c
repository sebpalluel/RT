/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:32:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:23:54 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_swap(void *a, void *b, size_t nbytes)
{
	unsigned char	*cur_a;
	unsigned char	*cur_b;
	unsigned char	tmp;
	size_t			i;

	cur_a = (unsigned char *)a;
	cur_b = (unsigned char *)b;
	i = 0;
	while (i < nbytes)
	{
		tmp = cur_a[i];
		cur_a[i] = cur_b[i];
		cur_b[i] = tmp;
		i++;
	}
}
