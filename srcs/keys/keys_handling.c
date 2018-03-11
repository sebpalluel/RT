/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:54:56 by mbeilles          #+#    #+#             */
/*   Updated: 2018/02/23 06:54:21 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"

t_key					*init_keys(void)
{
	t_key				*k;

	if (!(k = (t_key*)malloc((KEY_MAX) * sizeof(t_key))))
		exit(EXIT_FAILURE);
	k[0] = create_key(1, create_codes(1, SDL_SCANCODE_ESCAPE), &exit_rt);
	k[1] = create_key(2, create_codes(2, SDL_SCANCODE_W,
				SDL_SCANCODE_LGUI), &exit_rt);
	k[2] = create_key(2, create_codes(2, SDL_SCANCODE_LGUI,
				SDL_SCANCODE_RETURN), &toggle_fullscreen);
	k[3] = create_key(1, create_codes(1, SDL_SCANCODE_EQUALS),
			&perspepective_up);
	k[4] = create_key(1, create_codes(1, SDL_SCANCODE_MINUS),
			&perspepective_down);
	k[5] = create_key(1, create_codes(1, SDL_SCANCODE_DOWN), &rpp_up);
	k[6] = create_key(1, create_codes(1, SDL_SCANCODE_UP), &rpp_down);
	k[7] = create_key(2, create_codes(2, SDL_SCANCODE_DOWN,
				SDL_SCANCODE_LGUI), &threshold_up);
	k[8] = create_key(2, create_codes(2, SDL_SCANCODE_UP,
				SDL_SCANCODE_LGUI), &threshold_down);
	k[9] = create_key(1, create_codes(1, SDL_SCANCODE_1), &expo_up);
	k[10] = create_key(1, create_codes(1, SDL_SCANCODE_2), &expo_down);
	return (k);
}

void					handle_keyboard(t_env *env)
{
	const uint8_t		*keys;
	int32_t				n;
	SDL_Scancode		i;
	static t_key		*k = NULL;

	keys = SDL_GetKeyboardState(&n);
	if (k == NULL)
		k = init_keys();
	i = ~0U;
	while (++i < KEY_MAX)
		if (is_combinason_pressed(k[i], keys))
		{
			k[i].func(env);
			env->refresh = 1;
		}
}
