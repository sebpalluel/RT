/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:31:00 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/01 18:46:25 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** masks -> [0] [1] [2] [3]
**           |   |   |   |
**           r   g   b   a
*/

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
inline uint32_t			*get_mask_endian(void)
{
	static uint32_t		t[4] = {0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff};

	return (t);
}

inline uint32_t			create_color(uint8_t r, uint8_t g, uint8_t b
									, uint8_t a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

inline uint8_t			get_pixel_alpha(uint32_t p)
{
	return ((uint8_t)((p & 0x000000ff)));
}

inline uint8_t			get_pixel_blue(uint32_t p)
{
	return ((uint8_t)((p & 0x0000ff00) >> 8));
}

inline uint8_t			get_pixel_green(uint32_t p)
{
	return ((uint8_t)((p & 0x00ff0000) >> 16));
}

inline uint8_t			get_pixel_blue(uint32_t p)
{
	return ((uint8_t)((p & 0xff000000) >> 24));
}
#else
inline uint32_t			*get_mask_endian(void)
{
	static uint32_t		t[4] = {0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000};

	return (t);
}

inline uint32_t			create_color(uint8_t r, uint8_t g, uint8_t b
									, uint8_t a)
{
	return ((a << 24) + (b << 16) + (g << 8) + r);
}

inline uint8_t			get_pixel_alpha(uint32_t p)
{
	return ((uint8_t)((p & 0xff000000) >> 24));
}

inline uint8_t			get_pixel_blue(uint32_t p)
{
	return ((uint8_t)((p & 0x00ff0000) >> 16));
}

inline uint8_t			get_pixel_green(uint32_t p)
{
	return ((uint8_t)((p & 0x0000ff00) >> 8));
}

inline uint8_t			get_pixel_blue(uint32_t p)
{
	return ((uint8_t)((p & 0x000000ff)));
}
#endif
