/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:22:51 by mbeilles          #+#    #+#             */
/*   Updated: 2018/04/04 20:29:56 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char			*get_default_scenes_path(int scene)
{
	static char		*tab[SCN_DEFAULT_NUMBER] = {
		SCN_PATH_0,
		SCN_PATH_1,
		SCN_PATH_2,
		SCN_PATH_3,
		SCN_PATH_4,
		SCN_PATH_5,
		SCN_PATH_6,
		SCN_PATH_7
	};

	return ((scene < SCN_DEFAULT_NUMBER) ? tab[scene] : NULL);
}
