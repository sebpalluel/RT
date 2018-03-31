/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:55:13 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/31 17:02:32 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <SDL.h>
#include "/Users/seb/.brew/Cellar/sdl2/2.0.8/include/SDL2/SDL.h"
#include "./includes/rt.h"
#include "./includes/graphical_manager.h"

uint32_t			update_graphical_manager(t_kernal_event e)
{
	if (e.type == EK_WINDOW_REFRESH)
}

SDL_Surface                        *dup_surface(SDL_Surface *sf)
{
	SDL_Surface *s;

	if (!(s = SDL_CreateRGBSurface(0, sf->w, sf->h, 32, mask[0], mask[1], \
					mask[2], mask[3])))
		exit(EXIT_FAILURE);
	SDL_BlitSurface(sf, NULL, s, NULL);
	return (s);
}

void				apply_post_effect(t_cam *cam, t_post_effect e)
{
	uint32_t		i;
	SDL_Surface		*cpy;
	int				x;
	int				y;

	i = 0;
	while (cam->frames[i])
	{
		/*if (cam->frames_state[i] == FS_DONE && */
		/*(cpy = dup_surface(cam->frames[i])))*/
		if (cam->frames_state[i] == FS_DONE)
		{
			y = -1;
			while (++y < s->h)
			{
				x = -1;
				while (++x < s->w)
					set_pixel(s, x, y, postprocess()[cam->effect](s, x, y));
			}
			/*cpy = postprocess()[cam->effect](cpy);*/
			/*SDL_BlitSurface(cpy, NULL, cam->frames[i], NULL);*/
			/*SDL_FreeSurface(cpy);*/
		}
		cam->frames_state[i] = FS_PROCCESSED;
	}
	i++;
}
}
