/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coladd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:50:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:55:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_col		ft_coladd(t_col col1, t_col col2)
{
	t_col	col;

	col.r = col1.r + col2.r;
	if (col.r > 1)
		col.r = 1;
	col.g = col1.g + col2.g;
	if (col.g > 1)
		col.g = 1;
	col.b = col1.b + col2.b;
	if (col.b > 1)
		col.b = 1;
	return (col);
}
