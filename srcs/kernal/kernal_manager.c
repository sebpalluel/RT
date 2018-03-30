/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernal_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 00:45:08 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 18:03:51 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernal.h"
#include "display_manager.h"

uint32_t			poll_kernal_event(t_kernal_event *e)
{
	*e = pop_kernal_event();
	return (e->type == EK_NONE);
}

void				resolve_events(void)
{
	t_kernal_event	e;

	display_manager_event_watcher();
	while (poll_kernal_event(&e))
		g_kernal_resolvers[e.type](e);
}
