/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_display_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:17:12 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 18:41:29 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <SDL.h>
#include "display_manager.h"
#include "rt.h"
#include "libft.h"

#define ERR_DISPLAY_MSG	"Display manager allocation failed"
#define ERR_WINDOW_MSG	"Window allocation failed"

static inline void		destroy_scene(t_scene *scene)
{
	/*ft_lstdel(scene->forms, &ft_dellistelem);*/
	/*ft_lstdel(scene->lgts, &ft_dellistelem);*/
	/*ft_lstdel(scene->cams, &ft_dellistelem);*/
	scene->forms = NULL;
	scene->lgts = NULL;
	scene->cams = NULL;
	free(scene);
}

inline void				destroy_dwindow(t_window *win)
{
	pthread_cancel(*win->thread);
	SDL_DestroyWindow(win->window);
	destroy_scene(win->scene);
	free(win);
}

static inline t_window	*create_window(t_window_data data)
{
	t_window			*win;

	if (!(win = (t_window*)malloc(sizeof(t_window))) &&
		!(win->thread = (pthread_t*)malloc(sizeof(pthread_t))) &&
		!(win->window = SDL_CreateWindow(data.title, data.x, data.y
										, data.w, data.h, data.flags)))
		leave(STR_ERR(ERR_WINDOW_MSG, "003"), EXIT_FAILURE);
	win->original_data = data;
	win->thread = NULL;
	win->surface = SDL_GetWindowSurface(win->window);
	win->next = NULL;
	return (win);
}

inline t_window			*create_dwindow(t_window_data data)
{
	t_window			*w1;
	t_window			*w2;

	w1 = g_display_manager.win;
	w2 = create_window(data);
	w2->next = w1;
	g_display_manager.win = w2;
	g_display_manager.windows_managed++;
	/*push_kernal_event((t_kernal_event){EK_WINDOW_FOCUSED, w2});*/
	SDL_RaiseWindow(w2->window);
	return (w2);
}

/*inline void				create_cli(void)*/
/*{*/
	/*t_window_data		data;*/

	/*if (g_display_manager.cli)*/
	/*{*/
		/*ft_putstr(STR_WRN("CLi is already created!", WRN_SEV_MINOR));*/
		/*return ;*/
	/*}*/
	/*if (SDL_GetDesktopDisplayMode(0, &sdl_dm))*/
		/*data = (t_window_data){0, 0, sdl_dm.w / 2, sdl_dm.h / 2, " "*/
						/*, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE});*/
	/*else*/
		/*data = (t_window_data){SDL_WINDOWPOS_CENTERED*/
						/*, SDL_WINDOWPOS_CENTERED*/
						/*, DEFAULT_WIN_W, DEFAULT_WIN_H, " "*/
						/*, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE});*/
	/*g_display_manager.cli = create_dwindow(data);*/
/*}*/

#undef ERR_DISPLAY_MSG
#undef ERR_WINDOW_MSG
