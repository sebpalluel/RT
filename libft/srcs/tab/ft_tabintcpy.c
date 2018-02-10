/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabintcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 16:55:15 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 16:30:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			**ft_tabintcpy(int **array, size_t width)
{
	int		**tab;
	size_t	i;

	if (array)
	{
		if (!(tab = (int **)malloc(sizeof(int *) * \
						(ft_tablen((char **)array) + 1))))
			return (NULL);
		i = 0;
		while (array[i])
		{
			tab[i] = ft_intdup(array[i], width);
			i++;
		}
		tab[i] = 0;
		return (tab);
	}
	return (NULL);
}
