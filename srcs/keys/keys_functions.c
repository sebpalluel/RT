/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:54:27 by mbeilles          #+#    #+#             */
/*   Updated: 2018/02/22 21:23:17 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"

void					rpp_down(t_env *env)
{
	if (env->rpp > 1)
		env->rpp--;
	env->rpp_alt = env->rpp;
}

void					expo_up(t_env *env)
{
	if (env->expo < 420)
		env->expo *= 1.01;
	env->rpp_alt = env->rpp;
}

void					expo_down(t_env *env)
{
	if (env->expo > 0)
		env->expo /= 1.01;
	env->rpp_alt = env->rpp;
}

void					threshold_up(t_env *env)
{
	if (env->rpp_threshold < 42)
		env->rpp_threshold++;
	env->rpp_alt = env->rpp;
	env->refresh = 1;
}

void					threshold_down(t_env *env)
{
	if (env->rpp_threshold > 1)
		env->rpp_threshold--;
	env->rpp_alt = env->rpp;
}
