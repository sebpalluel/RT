/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:10:24 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 19:15:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*
** =============================================================================
** 							Includes
** =============================================================================
*/

//# include <SDL.h>
# include "/Users/seb/.brew/include/SDL2/SDL.h"
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

typedef void				(*t_key_func)(t_env *);

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

void						handle_keyboard(t_env *env);

uint32_t					is_combinason_pressed(t_key k, const uint8_t *keys);
SDL_Scancode				*create_codes(int32_t codes, ...);
t_key						create_key(uint32_t keys, SDL_Scancode *codes
										, t_key_func f);

void						exit_rt(t_env *env);
void						toggle_fullscreen(t_env *env);
void						perspepective_up(t_env *env);
void						perspepective_down(t_env *env);
void						rpp_up(t_env *env);
void						rpp_down(t_env *env);
void						expo_up(t_env *env);
void						expo_down(t_env *env);
void						threshold_up(t_env *env);
void						threshold_down(t_env *env);

/*
** =============================================================================
*/

#endif
