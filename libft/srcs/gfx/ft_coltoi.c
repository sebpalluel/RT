/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coltoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:00:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 16:03:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			ft_coltoi(t_col col)
{
	return ((((int)(col.r * 0xff0000)) & 0xff0000) +
			(((int)(col.g * 0xff00)) & 0xff00) +
			(((int)(col.b * 0xff)) & 0xff));
}
