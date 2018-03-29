/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:57:34 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 10:05:19 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICAL_MANAGER_H
# define GRAPHICAL_MANAGER_H

# include "display_manager.h"
# include "kernal.h"

typedef enum			e_post_effect
{
	PP_SEPIA,
	PP_CELL_SHADING,
	PP_NEGATIVE,
	PP_BLACK_WHITE,
	PP_BLUR,
	PP_MAX
}						t_post_effect;

void					apply_post_effect(t_scene *s, t_post_effect e);

void					ft_sepia();
void					ft_cel_shading();
void					ft_negative();
void					ft_blackandwhite();
void					ft_blur();

#endif
