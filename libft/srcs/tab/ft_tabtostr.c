/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:08:28 by psebasti          #+#    #+#             */
/*   Updated: 2018/01/11 17:20:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				get_size(char **tab)
{
	size_t			size;
	size_t			nb_str;

	size = 0;
	nb_str = 0;
	if (tab)
	{
		while (*tab)
		{
			size += ft_strlen(*tab);
			tab++;
			nb_str++;
		}
	}
	return (size + nb_str - 1);
}

char				*ft_tabtostr(char **tab)
{
	char			*str;
	size_t			size;
	char			*tmp;

	size = get_size(tab);
	str = ft_strnew(size);
	if (tab && str)
	{
		while (*tab)
		{
			ft_strcat(str, *tab);
			tab++;
			tmp = ft_strchr(str, 0);
			tmp[0] = (*tab == NULL) ? '\0' : ' ';
		}
		return (str);
	}
	return (NULL);
}
