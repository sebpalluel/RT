/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_keytoletterchar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 18:59:35 by psebasti          #+#    #+#             */
/*   Updated: 2017/08/21 18:31:40 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_mlx_keytoletterchar3(int keycode)
{
	if (keycode == C_KEY)
		return ('c');
	else if (keycode == V_KEY)
		return ('v');
	else if (keycode == B_KEY)
		return ('b');
	else if (keycode == N_KEY)
		return ('n');
	else if (keycode == M_KEY)
		return ('m');
	return ('\0');
}

static char	ft_mlx_keytoletterchar2(int keycode)
{
	if (keycode == P_KEY)
		return ('p');
	else if (keycode == A_KEY)
		return ('a');
	else if (keycode == S_KEY)
		return ('s');
	else if (keycode == D_KEY)
		return ('d');
	else if (keycode == F_KEY)
		return ('f');
	else if (keycode == G_KEY)
		return ('g');
	else if (keycode == H_KEY)
		return ('h');
	else if (keycode == J_KEY)
		return ('j');
	else if (keycode == K_KEY)
		return ('k');
	else if (keycode == L_KEY)
		return ('l');
	else if (keycode == Z_KEY)
		return ('z');
	else if (keycode == X_KEY)
		return ('x');
	return (ft_mlx_keytoletterchar3(keycode));
}

char		ft_mlx_keytoletterchar(int keycode)
{
	if (keycode == Q_KEY)
		return ('q');
	else if (keycode == W_KEY)
		return ('w');
	else if (keycode == E_KEY)
		return ('e');
	else if (keycode == R_KEY)
		return ('r');
	else if (keycode == T_KEY)
		return ('t');
	else if (keycode == Y_KEY)
		return ('y');
	else if (keycode == U_KEY)
		return ('u');
	else if (keycode == I_KEY)
		return ('i');
	else if (keycode == O_KEY)
		return ('o');
	return (ft_mlx_keytoletterchar2(keycode));
}
