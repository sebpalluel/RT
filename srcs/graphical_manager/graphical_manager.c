/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:55:13 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/05 18:41:21 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "rt.h"
#include "graphical_manager.h"

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

uint32_t						update_graphical_manager(t_kernal_event e)
{
	return (0);
}

typedef uint32_t				(*t_cases)(SDL_Event);

void							graphical_manager_event_watcher(void)
{
	static t_cases				cases[3] = {&case_quit, &case_resize, &case_mouse};
	uint32_t					ke_type[3] = {EK_QUIT, EK_RESIZE, EK_MOUSE};
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
