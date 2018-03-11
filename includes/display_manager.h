/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:58:16 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/03 16:29:09 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_HANDLER_H
# define SDL_HANDLER_H

# include <SDL.h>

#define DEFAULT_WIDTH	3840
#define DEFAULT_HEIGHT	2160

#define DEFAULT_WIN_W	1920
#define DEFAULT_WIN_H	1080

typedef struct			s_cam
{
	t_vec3				pos;
	t_vec3				frt;
	t_vec3				rgt;
	t_vec3				dwn;
	SDL_Surface			**frames;
	uint32_t			frame_number;
}						t_cam;

typedef struct			s_window_data
{
	int32_t				x;
	int32_t				y;
	int32_t				w;
	int32_t				h;
	uint32_t			flags;
	char				*title;
}						t_window_data;

typedef struct			s_window
{
	SDL_Window			*window;
	SDL_Surface			*surface;
	t_window_data		original_data;
	struct s_window		*next;
}						t_window;

typedef struct			s_display_manager
{
	t_window			*win;
	t_window			*cli;
	uint32_t			windows_managed;
	t_window			scene_focused;
}						t_display_manager;

void					init_cam_buffers(t_cam *cam, uint32_t frames);
t_display_manager		*create_display_manager(void);

typedef void		(*t_update_dm_func)(t_dm_data);

#endif
