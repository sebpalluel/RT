/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_keytonumchar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 20:26:39 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 13:07:32 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_mlx_keytonumchar(int keycode)
{
	if (keycode == ZERO)
		return ('0');
	else if (keycode == ONE)
		return ('1');
	else if (keycode == TWO)
		return ('2');
	else if (keycode == THREE)
		return ('3');
	else if (keycode == FOUR)
		return ('4');
	else if (keycode == FIVE)
		return ('5');
	else if (keycode == SIX)
		return ('6');
	else if (keycode == SEVEN)
		return ('7');
	else if (keycode == EIGHT)
		return ('8');
	else if (keycode == NINE)
		return ('9');
	else if (keycode == MINUS)
		return ('-');
	else
		return ('\0');
}
