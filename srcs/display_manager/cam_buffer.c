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
	if (!(cam->frames = (SDL_Surface**)malloc(frames * sizeof(SDL_Surface*))))
		leave(STR_ERR("001", "Fail allocating camera frames"), EXIT_FAILURE);
	i = ~0U;
	cam->frame_number = frames;
	while (++i < frames)
	{
		if (!(cam->frames[i] = SDL_CreateRGBSurface(0
						, DEFAULT_WIDTH / i, DEFAULT_HEIGHT / i
						, 32, mask[0], mask[1], mask[2], mask[3])))
			leave(STR_ERR("002", ""), EXIT_FAILURE);
	}
	return (0);
}
