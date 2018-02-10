/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:21:46 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 15:22:11 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printstrarray(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
}
