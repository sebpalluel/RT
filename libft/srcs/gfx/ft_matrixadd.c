/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:45:39 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 17:28:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_matrixadd(t_matrix *a, t_matrix *b)
{
	int		x;
	int		y;

	if (a->i != b->i || a->j != b->j)
		return ;
	x = -1;
	while (++x < a->i && (y = -1))
		while (++y < a->j)
			a->mat[x][y] += b->mat[x][y];
}
