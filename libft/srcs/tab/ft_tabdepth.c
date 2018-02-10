/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdepth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:05:52 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 17:46:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_tabdepth(void **tab)
{
	size_t	depth;

	depth = 0;
	if (tab && *tab)
	{
		while (tab[depth])
			depth++;
	}
	return (depth);
}
