/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmatch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:21:08 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/18 19:27:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nmatch(char *s1, char *s2)
{
	if (*s1 == 0 && *s2 == 0)
		return (1);
	else if (*s1 != *s2 && *s2 != '*')
		return (0);
	else if (*s1 == *s2 && *s1 != '*')
		return (nmatch(s1 + 1, s2 + 1));
	else if (*s2 == '*')
	{
		if (*s1 == 0)
			return (nmatch(s1, s2 + 1));
		return ((nmatch(s1, s2 + 1)) + (nmatch(s1 + 1, s2)));
	}
	else
		return (0);
}
