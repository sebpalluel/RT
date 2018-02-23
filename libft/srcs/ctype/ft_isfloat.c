/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:16:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/21 17:27:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_checksignerr(char *s)
{
	t_bool		get_sign;

	get_sign = FALSE;
	while (ft_isspace(*s) == OK || *s == '-' || *s == '+')
	{
		if (*s == '-' || *s == '+')
		{
			if (get_sign)
				return (NULL);
			get_sign = TRUE;
		}
		s++;
	}
	return (s);
}

static t_bool	ft_checknumerror(char *s)
{
	t_bool		dot;
	t_bool		get_num;
	t_bool		get_space;

	dot = FALSE;
	get_num = FALSE;
	get_space = FALSE;
	while (s && *s)
	{
		if ((*s != '.' && ft_isspace(*s) != OK) && (*s < '0' || *s > '9'))
			return (ERROR);
		else if (!get_num && *s >= '0' && *s <= '9')
			get_num = TRUE;
		else if (*s == '.')
		{
			if (dot == TRUE || !get_num)
				return (ERROR);
			dot = TRUE;
		}
		while (*s && ft_isspace(*s) == OK && s++)
			if (*s && ft_isspace(*s) != OK)
				return (ERROR);
		if (*s)
			s++;
	}
	return (OK);
}

t_bool			ft_isfloat(char *s)
{

	if (!s || !*s)
		return (ERROR);
	if (!(s = ft_checksignerr(s)))
		return (ERROR);
	return (ft_checknumerror(s));
}
