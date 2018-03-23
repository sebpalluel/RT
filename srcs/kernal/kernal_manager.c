/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernal_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 00:45:08 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/04 00:48:06 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernal.h"

void				resolve_events(void)
{
	t_kernal_event	e;

	while (42)
	{
		if (wait_event(&e))
			g_kernal_resolvers[e.type](e);
	}
}

void				init_kernal_engine(void)
{
	
}
