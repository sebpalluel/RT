/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:55:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:56:30 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_col		ft_col_r(double r, double g, double b, double s)
{
	t_col	col;

	col.r = r;
	col.g = g;
	col.b = b;
	col.s = s;
	return (col);
}
