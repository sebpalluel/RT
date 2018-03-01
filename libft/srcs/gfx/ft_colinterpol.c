/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colinterpol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:57:31 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:58:33 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_col		ft_colinterpol(t_col col1, t_col col2, double t)
{
	t_col	col;

	col.r = col1.r * (1 - t) + col2.r * t;
	col.g = col1.g * (1 - t) + col2.g * t;
	col.b = col1.b * (1 - t) + col2.b * t;
	return (col);
}
