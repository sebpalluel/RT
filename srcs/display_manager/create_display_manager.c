/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_display_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:17:12 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 16:49:04 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display_manager.h"
#include "rt.h"

#define ERR_DISPLAY_MSG	"Display manager allocation failed"
#define ERR_WINDOW_MSG	"Window allocation failed"

static inline t_window	*create_window(t_window_data data)
{
	t_window			*win;

	if (!(win = (t_window*)malloc(sizeof(t_window))) &&
		!(win->window = SDL_CreateWindow(data.title, data.x, data.y
										, data.w, data.h, data.flags)))
		leave(STR_ERR("103", ERR_WINDOW_MSG));
	win->original_data = data;
	win->surface = SDL_GetWindowSurface(win->window);
	win->next = NULL;
	return (win);
}

t_display_manager		*create_display_manager(void)
{
	t_display_manager	*dm;
	SDL_DisplayMode		sdl_dm;

	if (!(dm = (t_display_manager)malloc(sizeof(t_display_manager))))
		leave(STR_ERR("101", ERR_MSG), EXIT_FAILURE);
	if (SDL_GetDesktopDisplayMode(0, &sdl_dm))
		dm->win = create_window((t_window_data){0, 0, sdl_dm.w / 2, sdl_dm.h / 2
						, TITLE
						, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE});
	else
		dm->win = create_window((t_window_data){SDL_WINDOWPOS_CENTERED
						, SDL_WINDOWPOS_CENTERED
						, DEFAULT_WIN_W, DEFAULT_WIN_H, TITLE
						, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE});
	dm->cli = dm->win;
	dm->windows_managed = 1;
	return (dm);
}

#undef ERR_MSG
