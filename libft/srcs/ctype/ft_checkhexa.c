/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:07:39 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/03 12:16:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_checkhexa(char *str)
{
	size_t			i;
	size_t			hexa_count;
	size_t			prefix;

	i = 0;
	hexa_count = 0;
	prefix = 0;
	while (str[i])
	{
		if (i == 0 && str[0] == '0' && str[1] == 'x')
		{
			prefix = 1;
			i += 2;
		}
		if (prefix && ft_ishexa(str[i]) == OK && hexa_count < 7)
			hexa_count++;
		else
			return (ERROR);
		i++;
	}
	return (OK);
}
