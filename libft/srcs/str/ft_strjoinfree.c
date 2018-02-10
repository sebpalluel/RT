/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:37:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/15 19:49:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, size_t mode)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (s1 && mode == 1)
		free(s1);
	else if (s2 && mode == 2)
		free(s2);
	else if (s1 && s2 && mode == 0)
	{
		free(s1);
		free(s2);
	}
	return (tmp);
}
