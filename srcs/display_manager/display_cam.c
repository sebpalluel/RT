/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 03:37:18 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 10:57:01 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display_manager.h"
#include "rt.h"

static inline uint32_t	get_pixel(SDL_Surface *s, uint32_t x, uint32_t y)
{
	return(*(((uint8_t*)s->pixels) + (y * s->pitch + x * (sizeof(uint32_t)))));
}

static inline void		set_pixel(SDL_Surface *s, uint32_t x, uint32_t y
									, uint32_t pixel)
{
	*(((uint8_t*)s->pixels) + (y * s->pitch + x * (sizeof(uint32_t)))) = pixel;
}

uint32_t				*render(t_scene *sc, SDL_Surface *sf
		, t_rect r, t_cam *cam)
{
	t_rect				p;

	p = (t_rect){r.x - 1, r.y - 1, 0, 0};
	while (++p.y < r.w)
	{
		p.x = r.x - 1;
		while (++p.x < r.w)
			set_pixel(sf, p.x, p.y, ft_coltoi(send_ray(calculate_ray(p.h, p.w
														, cam, sf), scene)));
	}
	return (1);
}

void					display_best_cam_buffer(t_cam *cam, t_window *win)
{
	uint32_t			s_index;

	s_index = 0;
	while (s_index < cam->frame_number && cam->frames_state[s_index] == FS_DONE)
		s_index++;
	SDL_BlitScaled(cam->frames[s_index], NULL, win->surface, NULL);
}

void					draw_cam_stack(t_drawing_data data)
{
	uint32_t			i;

	ft_memset(data.cam->frames_state, sizeof(uint32_t) * data.cam->frame_number
			, FS_CALCULATING);
	i = ~0U;
	while (++i < data.cam->frame_number)
		/*uint32_t		ft_raytracing(t_scene *scene, SDL_Surface *surface)*/
		if (render(data.scene, data.cam->frames[i]))
		{
			data.cam->frames_state[i] = FS_DONE;
			push_kernal_event((t_kernal_event){EK_WINDOW_REFRESH, data});
		}
		else
			SDL_Log("Error in the render of frame %d, in the window %d\n"
					, i, data.window_id);
}
