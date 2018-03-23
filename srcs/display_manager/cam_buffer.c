/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:07:32 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 16:57:45 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display_manager.h"
#include "rt.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
static inline uint32_t	*get_mask_endian(void)
{
	return ({0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff});
}
#else
static inline uint32_t	*get_mask_endian(void)
{
	return ({0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000});
}
#endif

void					init_cam_buffers(t_cam *cam, uint32_t frames)
{
	uint32_t			*mask;
	uint32_t			i;

	mask = get_mask_endian();
	if (!(cam->frames = (SDL_Surface**)malloc(frames * sizeof(SDL_Surface*)))
			|| !(cam->frames_state = (uint32_t*)malloc(sizeof(uint32_t)
														* frames)))
		leave(STR_ERR("001", "Fail allocating camera frames"), EXIT_FAILURE);
	i = ~0U;
	cam->frame_number = frames;
	while (++i < frames)
	{
		if (!(cam->frames[i] = SDL_CreateRGBSurface(0
							, DEFAULT_WIDTH / i, DEFAULT_HEIGHT / i
							, 32, mask[0], mask[1], mask[2], mask[3])))
			leave(STR_ERR("002", "Fail creating frames"), EXIT_FAILURE);
	}
	ft_memset(cam->frames_state, sizeof(uint32_t) * frames, FS_DIRTY);
	return (0);
}

void					display_best_cam_buffer(t_cam *cam, t_window *win)
{
	uint32_t			s_index;

	s_index = 0;
	while (s_index < cam->frame_number && cam->frames_state[s_index] == FS_DONE)
		s_index++;
	SDL_BlitScaled(cam->frames[s_index], NULL, win->surface, NULL);
}

void					draw_cam_stack(t_thread_data data)
{
	uint32_t			i;

	ft_memset(data.cam->frames_state, sizeof(uint32_t) * data.cam->frame_number
			, FS_CALCULATING);
	i = ~0U;
	while (++i < data.cam->frame_number)
		/*ft_raytracing(t_scene *scene, SDL_Surface *surface)*/
		if (ft_raytracing(data.scene, data.cam->frames[i]))
		{
			data.cam->frames_state[i] = FS_DONE;
			push_kernal_event((t_kernal_event){EK_WINDOW_REFRESH, data});
		}
		else
			SDL_Log("Error in the render of frame %d, in the window %d\n"
				, i, data.window_id);

}
