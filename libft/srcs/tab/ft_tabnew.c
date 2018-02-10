/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnewsize_t.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 20:09:13 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/04 17:22:31 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	**ft_tabnewsize_t(size_t width, size_t height)
{
	size_t	i;
	size_t	**tab;

	i = 0;
	tab = (size_t **)ft_memalloc(sizeof(size_t *) * (height + 1));
	while (tab && i < height)
	{
		tab[i] = (size_t *)ft_memalloc(sizeof(size_t) * width);
		i++;
	}
	tab[height] = NULL;
	return (tab);
}
