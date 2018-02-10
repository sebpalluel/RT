/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab3newstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:31:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 12:34:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	***ft_tab3newstr(size_t width, size_t height)
{
	size_t	i;
	char	***tab;

	i = 0;
	tab = (char ***)ft_memalloc(sizeof(char **) * (height + 1));
	while (tab && i < height)
	{
		tab[i] = (char **)ft_memalloc(sizeof(char*) * width + 1);
		tab[i][width] = NULL;
		i++;
	}
	tab[height] = NULL;
	return (tab);
}
