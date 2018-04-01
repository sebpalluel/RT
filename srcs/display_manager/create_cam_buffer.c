/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cam_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:46:44 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/01 18:39:03 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline void				leave(char *str, uint32_t exit_code)
{
	if (str)
		ft_putstr(str);
	ft_putstr(STR_INF("Exiting"NICK));
	exit(exit_code);
}

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
}
