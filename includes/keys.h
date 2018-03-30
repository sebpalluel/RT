/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:10:24 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 18:29:38 by mbeilles         ###   ########.fr       */
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

typedef void				(*t_key_func)();

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

void						handle_keyboard();

uint32_t					is_combinason_pressed(t_key k, const uint8_t *keys);
SDL_Scancode				*create_codes(int32_t codes, ...);
t_key						create_key(uint32_t keys, SDL_Scancode *codes
										, t_key_func f);

void						exit_rt();
void						toggle_fullscreen();
void						perspepective_up();
void						perspepective_down();
void						rpp_up();
void						rpp_down();
void						expo_up();
void						expo_down();
void						threshold_up();
void						threshold_down();

/*
** =============================================================================
*/

#endif
