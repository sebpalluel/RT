/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 13:02:37 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/05 18:19:13 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNAL_H
# define KERNAL_H

# include <stdint.h>
# include <stdio.h>

/*
** =============================================================================
*/

typedef enum				e_kernal_event_type
{
	EK_UNKNOWN = 0,
	EK_QUIT,
	EK_RESIZE,
	EK_KEYPRESS,
	EK_KEYRELEASE,
	EK_MOUSE
}							t_ke_type;

typedef union				u_kernal_event_data
{
	uint32_t				pad;
}							t_ke_data;

typedef struct				s_kernal_event
{
	t_ke_type				type;
	t_ke_data				data;
}							t_kernal_event;

typedef struct				s_kernal_stack
{
	t_kernal_event			event;
	struct s_kernal_stack	*prev;
	struct s_kernal_stack	*next;
}							t_kernal_stack;

/*
** =============================================================================
*/

typedef struct				s_kernal
{
	t_kernal_stack			*first_stack;
	t_kernal_stack			*last_stack;
	uint32_t				stack_pushed;
}							t_kernal;

/*
** =============================================================================
** 							Globals
** =============================================================================
*/

# define KERNAL_EVENT_BUFFER	1 << 21
# define KERNAL_EVENT_NULL		((t_kernal_event){EK_UNKNOWN, 0})

extern t_kernal				g_kernal;
t_kernal					g_kernal = (t_kernal)
{
	.first_stack = NULL,
	.last_stack = NULL,
	.stack_pushed = 0
};

extern t_kernal_stack		g_kernal_stack[KERNAL_EVENT_BUFFER];
t_kernal_stack				g_kernal_stack[KERNAL_EVENT_BUFFER];

/*
** =============================================================================
** 							Function protos
** =============================================================================
*/

uint32_t					push_kernal_event(t_kernal_event e);
t_kernal_event				pop_kernal_event(void);
uint32_t					wait_event(t_kernal_event *e);

/*
** =============================================================================
** 							Resolver
** =============================================================================
*/

# define KERNAL_RESOLVERS	1

typedef void				(*t_ke_func)(t_kernal_event);

/*
** =============================================================================
*/

extern t_ke_func			g_kernal_resolvers[KERNAL_RESOLVERS];
t_ke_func					g_kernal_resolvers[KERNAL_RESOLVERS] =
{
	NULL
};

/*
** =============================================================================
** 							Resolver
** =============================================================================
*/

void						resolve_events(void);

#endif
