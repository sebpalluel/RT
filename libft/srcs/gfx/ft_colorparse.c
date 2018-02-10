/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colorparse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:52:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:16:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color		*ft_colorparse(char *arg)
{
	char	**arg_color;

	if (ft_strlen(arg) < 5 || ft_strlen(arg) > 11)
		return (NULL);
	arg_color = ft_strsplit(arg, ',');
	if (!arg_color || !arg_color[0] || !arg_color[1] || !arg_color[2])
		return (NULL);
	return (ft_colornew((unsigned char)ft_atoi(arg_color[0]), \
				(unsigned char)ft_atoi(arg_color[1]), \
				(unsigned char)ft_atoi(arg_color[2])));
}
