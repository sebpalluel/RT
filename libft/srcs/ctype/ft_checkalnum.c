/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkalnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 15:47:24 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/20 15:48:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_checkalnum(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (OK);
}
