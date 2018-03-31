/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:10:24 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/31 11:08:18 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*
** =============================================================================
** 							Includes
** =============================================================================
*/

# include <SDL.h>
//# include "/Users/seb/.brew/include/SDL2/SDL.h"
# include "rt.h"

/*
** =============================================================================
** 							Defines
** =============================================================================
*/

# define KEY_MAX			11

/*
** =============================================================================
** 							Typedefs
** =============================================================================
*/

typedef void				(*t_key_func)(void);

typedef struct				s_key
{
	uint32_t				keys;
	SDL_Scancode			*keycodes;
	t_key_func				func;
}							t_key;

/*
** =============================================================================
** 							Prototypes
** =============================================================================
*/

t_key						*init_keys(void);

void						handle_keyboard(void);

uint32_t					is_combinason_pressed(t_key k, const uint8_t *keys);
SDL_Scancode				*create_codes(int32_t codes, ...);
t_key						create_key(uint32_t keys, SDL_Scancode *codes
										, t_key_func f);

void						exit_rt(void);
void						toggle_fullscreen(void);
void						perspepective_up(void);
void						perspepective_down(void);
void						rpp_up(void);
void						rpp_down(void);
void						expo_up(void);
void						expo_down(void);
void						threshold_up(void);
void						threshold_down(void);

/*
** =============================================================================
*/

#endif
