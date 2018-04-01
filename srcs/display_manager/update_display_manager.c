/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_display_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 12:36:07 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/01 17:13:23 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** =============================================================================
** 								Case Functions
** =============================================================================
*/

uint32_t						case_quit(SDL_Event e)
{
	return (e.type == SDL_QUIT);
}

uint32_t						case_resize(SDL_Event e)
{
	return (e.type == SDL_WINDOWEVENT && e.window.event);
}

uint32_t						case_mouse(SDL_Event e)
{
	return (e.type == SDL_MOUSEMOTION);
}

/*
** =============================================================================
*/

static inline t_kernal_event	create_ke(t_ke_type type)
{
	return ((t_kernal_event){.type = type});
}

/*
** =============================================================================
** 								Functions
** 						(to be used outsite of this)
** =============================================================================
*/

typedef uint32_t				(*t_cases)(SDL_Event);

void							display_manager_event_watcher(void)
{
	static t_cases				cases[3] = {&case_quit, &case_resize, &case_mouse};
	static uint32_t				ke_type[3] = {EK_QUIT, EK_WINDOW_RESIZED, EK_MOUSE_MOTION};
	SDL_Event					e;
	t_kernal_event				ke;
	uint32_t					i;

	while (SDL_PollEvent(&e))
	{
		i = ~0U;
		while (++i < 3)
			if (cases[i])
				push_kernal_event(create_ke(ke_type[i]));
	}
}

uint32_t						refresh_dwindow(t_window *win)
{
	if (!display_best_frame(win->scene->cur_cam, win->surface, FS_PROCCESSED))
		if (!display_best_frame(win->scene->cur_cam, win->surface, FS_DONE))
		{
			ft_putstr(STR_WRN("Cam unable to refresh!", WRN_SEV_MINOR));
			return (0);
		}
	return (1);
}
