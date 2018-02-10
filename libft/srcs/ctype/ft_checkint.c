/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:08:35 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/03 12:47:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_checkint(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isint(str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (OK);
}
