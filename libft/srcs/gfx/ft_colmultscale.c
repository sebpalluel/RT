/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colmultscale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:52:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:53:17 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_col	ft_colmultscale(t_col col, double t)
{
	col.r = col.r * t;
	col.g = col.g * t;
	col.b = col.b * t;
	return (col);
}

