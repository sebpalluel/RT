/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:55:13 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/01 19:42:41 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "rt.h"
#include "graphical_manager.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
static inline uint32_t	*get_mask_endian(void)
{
	static uint32_t		t[4] = {0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff};

	return (t);
}
#else
static inline uint32_t	*get_mask_endian(void)
{
	static uint32_t		t[4] = {0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000};

	return (t);
}
#endif

SDL_Surface				*dup_surface(SDL_Surface *sf)
{
	SDL_Surface			*s;
	uint32_t			*mask;

	mask = get_mask_endian();
	if (!(s = SDL_CreateRGBSurface(0, sf->w, sf->h, 32, mask[0], mask[1], \
					mask[2], mask[3])))
		exit(EXIT_FAILURE);
	SDL_BlitSurface(sf, NULL, s, NULL);
	return (s);
}

void					apply_post_effect(t_cam *cam, t_post_effect e)
{
	uint32_t			i;
	SDL_Surface			*cpy;

	i = 0;
	while (cam->frames[i])
	{
		if (cam->frames_state[i] == FS_DONE && 
				(cpy = dup_surface(cam->frames[i])))
		{
			cpy = postprocess()[cam->effect](cpy);
			SDL_BlitSurface(cpy, NULL, cam->frames[i], NULL);
			SDL_FreeSurface(cpy);
			cam->frames_state[i] = FS_PROCCESSED;
		}
		i++;
	}
}
