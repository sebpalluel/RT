/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 18:11:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 18:12:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_matrixinit(t_matrix *mat, int i, int j)
{
	int		a;

	mat->i = i;
	mat->j = j;
	if (!(mat->mat = malloc(sizeof(double*) * i)))
		return (0);
	a = -1;
	while (++a < i)
		if (!(mat->mat[a] = ft_memalloc(sizeof(double) * j)))
			return (0);
	return (1);
}
