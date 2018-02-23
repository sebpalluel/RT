/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issize_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:18:34 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/21 17:19:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool			ft_issize_t(char *s)
{
	t_bool		get_num;

	get_num = FALSE;
	if (!s || !*s)
		return (ERROR);
	while (ft_isspace(*s) == OK)
		s++;
	while (s && *s)
	{
		if (ft_isspace(*s) != OK && (*s < '0' || *s > '9'))
			return (ERROR);
		else if (!get_num && *s >= '0' && *s <= '9')
			get_num = TRUE;
		while (*s && ft_isspace(*s) == OK && s++)
			if (*s && ft_isspace(*s) != OK)
				return (ERROR);
		if (*s)
			s++;
	}
	return (OK);
}
