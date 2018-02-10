/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_h_flip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:40:46 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:30:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fliprow(void *row, size_t columns, size_t nbytes)
{
	size_t	index;
	void	*tmp_a;
	void	*tmp_b;

	index = 0;
	if (columns > 0)
	{
		while (index < columns / 2)
		{
			tmp_a = (void *)(row + index);
			tmp_b = (void *)(row + columns - 1 - index);
			ft_swap(tmp_a, tmp_b, nbytes);
			index++;
		}
	}
}

void		ft_h_flip(void **array, size_t columns, size_t rows, size_t nbytes)
{
	size_t	row;

	row = 0;
	while (row < rows)
	{
		ft_fliprow(array[row], columns, nbytes);
		row++;
	}
}
