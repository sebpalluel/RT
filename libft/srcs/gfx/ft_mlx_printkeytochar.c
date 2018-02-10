/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_printkeytochar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 18:36:03 by psebasti          #+#    #+#             */
/*   Updated: 2017/08/21 18:30:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_specialchar(int keycode)
{
	if (keycode == DOT_KEY)
		return ('.');
	else if (keycode == MINUS)
		return ('-');
	return ('\0');
}

char		ft_mlx_printkeytochar(int keycode)
{
	if (ft_mlx_keytonumchar(keycode) != '\0')
		return (ft_mlx_keytonumchar(keycode));
	else if (ft_mlx_keytoletterchar(keycode) != '\0')
		return (ft_mlx_keytoletterchar(keycode));
	else if (ft_specialchar(keycode) != '\0')
		return (ft_specialchar(keycode));
	return ('\0');
}
