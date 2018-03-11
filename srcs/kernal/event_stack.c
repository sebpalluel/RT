/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 13:08:18 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/05 17:45:29 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernal.h"

uint32_t			push_kernal_event(t_kernal_event event)
{
	t_kernal_stack	*t;

	if (g_kernal.stack_pushed >= KERNAL_EVENT_BUFFER)
		return (0);
	t = g_kernal.last_stack;
	g_kernal.last_stack = g_kernal_stack + g_kernal.stack_pushed++;
	g_kernal.last_stack->event = event;
	g_kernal.last_stack->next = t;
	g_kernal.last_stack->prev = NULL;
	return (1);
}

t_kernal_event		pop_kernal_event(void)
{
	t_kernal_event	event;

	if (g_kernal.stack_pushed <= 0)
		return (KERNAL_EVENT_NULL);
	event = g_kernal.first_stack.event;
	g_kernal.first_stack = g_kernal.first_stack->prev;
	g_kernal.stack_pushed--;
	return (event);
}

uint32_t			wait_event(void)
{
	t_kernal_event	e;
	uint64_t		i;

	i = 0;
	while ((e = pop_kernal_event()).type != EK_UNKNOWN)
	{
		if (g_kernal_resolvers[e.type])
			g_kernal_resolvers[e.type](e);
		++i;
	}
	return (i);
}
