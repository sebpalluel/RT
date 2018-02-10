/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v_flip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:55:58 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:32:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_flipcolumn(void **array, size_t column, size_t rows,\
		size_t nbytes)
{
	size_t	row;
	void	*tmp_a;
	void	*tmp_b;

	row = 0;
	if (rows > 1)
	{
		while (row < rows / 2)
		{
			tmp_a = (void *)(array[row] + column);
			tmp_b = (void *)(array[rows - 1 - row] + column);
			ft_swap(tmp_a, tmp_b, nbytes);
			row++;
		}
	}
}

void		ft_v_flip(void **array, size_t columns, size_t rows, size_t nbytes)
{
	size_t	column;

	column = 0;
	while (column < columns)
	{
		ft_flipcolumn(array, column, rows, nbytes);
		column++;
	}
}
