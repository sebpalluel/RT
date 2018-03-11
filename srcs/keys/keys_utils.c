/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:03:51 by mbeilles          #+#    #+#             */
/*   Updated: 2018/02/13 12:57:21 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "libft.h"
#include "stdarg.h"

uint32_t				is_combinason_pressed(t_key k, const uint8_t *keys)
{
	uint32_t			i;
	uint32_t			n;

	i = 0;
	n = ~0U;
	while (++n < k.keys)
		if (keys[k.keycodes[n]])
			++i;
		else
			return (0);
	return (i);
}

void					destroy_keys(t_key *k, uint32_t len)
{
	uint32_t			i;

	i = ~0U;
	while (++i < len)
		free(k[i].keycodes);
	free(k);
}

SDL_Scancode			*create_codes(int32_t codes, ...)
{
	SDL_Scancode		*s;
	int32_t				i;
	va_list				l;

	if (!(s = (SDL_Scancode*)malloc(codes * sizeof(SDL_Scancode))))
		exit(EXIT_FAILURE);
	va_start(l, codes);
	i = ~0U;
	while (++i < codes)
		s[i] = va_arg(l, SDL_Scancode);
	va_end(l);
	return (s);
}

t_key					create_key(uint32_t k, SDL_Scancode *keys, t_key_func f)
{
	return ((t_key){k, keys, f});
}
