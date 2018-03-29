/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 13:02:37 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 18:55:35 by mbeilles         ###   ########.fr       */
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
	EK_WINDOW_CLOSE,
	EK_WINDOW_OPEN,
	EK_WINDOW_RESIZED,
	EK_WINDOW_REFRESH,
	EK_KEY_PRESS,
	EK_KEY_RELEASE,
	EK_MOUSE_MOTION,
	EK_MOUSE_PRESS,
	EK_MAX_EVENT,
	EK_SAFE_RANGE
}							t_ke_type;

typedef union				u_kernal_event_data
{
	void					*data;
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
uint32_t					wait_event(void);

/*
** =============================================================================
** 							Resolver
** =============================================================================
*/

typedef void				(*t_ke_func)(t_kernal_event);

/*
** =============================================================================
** 							Resolving fuctions
** =============================================================================
*/

# define KERNAL_RESOLVERS	10

void						resolve_events(void);

void						quit_all(t_kernal_event e);
void						gm_window_close(t_kernal_event e);
void						gm_window_open(t_kernal_event e);
void						gm_window_resizing(t_kernal_event e);
void						gm_window_refresh(t_kernal_event e);
void						im_key_handler(t_kernal_event e);
void						im_mouse_motion(t_kernal_event e);
void						im_mouse_press(t_kernal_event e);
void						im_mouse_release(t_kernal_event e);

/*
** =============================================================================
*/

extern t_ke_func			g_kernal_resolvers[KERNAL_RESOLVERS];
t_ke_func					g_kernal_resolvers[KERNAL_RESOLVERS] =
{
	//&quit_all,
	//&gm_window_close,
	//&gm_window_open,
	//&gm_window_resizing,
	//&gm_window_refresh,
	//&im_key_handler,
	//&im_key_handler,
	//&im_mouse_motion,
	//&im_mouse_press,
	//&im_mouse_release
};

#endif
extern t_ke_func			g_kernal_resolvers[KERNAL_RESOLVERS];
