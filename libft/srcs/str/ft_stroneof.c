/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroneof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:22:20 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/24 18:01:13 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stroneof(char c, char *str)
{
	int		i;

	if (str == NULL || c == '\0')
		return (ERROR);
	i = -1;
	while (str[++i])
		if (c == str[i])
			return (OK);
	return (ERROR);
}
