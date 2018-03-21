/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:33:59 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/21 17:34:49 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool		ft_checkascii(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isascii(str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (OK);
}
