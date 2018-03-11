/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:22:38 by esuits            #+#    #+#             */
/*   Updated: 2018/02/24 22:50:17 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "keys.h"

void					exit_rt(t_env *env)
{
	ft_putstr(HD"Exiting "NICK"!\n");
	exit(EXIT_SUCCESS);
}

void					toggle_fullscreen(t_env *env)
{
	uint32_t			flg;

	flg = SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (SDL_GetWindowFlags(env->win) & flg)
	{
		ft_putstr(STR_INF("Exiting fullscreen!\n"));
		SDL_SetWindowFullscreen(env->win, 0);
	}
	else
	{
		ft_putstr(STR_INF("Entering fullscreen!\n"));
		SDL_SetWindowFullscreen(env->win, flg);
	}
	env->rpp_alt = env->rpp;
}

void					perspepective_up(t_env *env)
{
	if (env->pers < 100)
		env->pers *= 1.1;
	env->rpp_alt = env->rpp;
}

void					perspepective_down(t_env *env)
{
	if (env->pers > 0)
		env->pers /= 1.1;
	env->rpp_alt = env->rpp;
}

void					rpp_up(t_env *env)
{
	if (env->rpp < 42)
		env->rpp++;
	env->rpp_alt = env->rpp;
}
