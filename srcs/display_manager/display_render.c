/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 15:02:18 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/01 16:51:52 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void			set_pixel(SDL_Surface *s, uint32_t x, uint32_t y
								, uint32_t p)
{
	*(((uint32_t*)s->pixels) + y * s->pitch + x) = p;
}

inline uint32_t		get_pixel(SDL_Surface *s, uint32_t x, uint32_t y)
{
	return (*(((uint32_t*)s->pixels) + y * s->pitch + x));
}

uint32_t			display_best_frame(t_cam *cam, SDL_Surface *s
										, t_frame_state state)
{
	uint32_t		i;

	i = 0;
	while (i < cam->frame_number && cam->frames_state[i] != state)
		i++;
	if (cam->frames_state[i] == state)
		return (1 + SDL_BlitScaled(cam->frames[i], NULL, s, NULL));
	return (0);
}

void				*thread_draw(t_draw_data data)
{
	uint32_t		i;
	t_rect			r;

	ft_memset(data.cam->frames_state, sizeof(*data.cam->frames_state)
			* data.cam->frame_number, FS_DIRTY);
	i = ~0U;
	while (++i < data.cam->frame_number)
	{
		r = (t_rect){~0U, ~0U, data.window->surface->h, data.window->surface->w};
		while (++r.y < r.w)
		{
			r.x = ~0U;
			while (++r.x < r.w)
				set_pixel(data.cam->surface, r.x, r.y,
						ft_coltoi(send_ray(calculate_ray(r.x, r.y, data.cam
									, data.window->surface), &data)));
		}
		data.cam->frames_state[i] = FS_DONE;
		//APPLY POST EFFECTS OR NOT, I DUNNO!
		data.cam->frames_state[i] = FS_PROCCESSED;
		push_kernal_event((t_kernal_event){EK_WINDOW_REFRESH, data.window});
	}
	pthread_exit(NULL);
}
