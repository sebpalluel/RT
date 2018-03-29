/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:57:34 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 14:56:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICAL_MANAGER_H
# define GRAPHICAL_MANAGER_H

# include "./display_manager.h"
# include "./kernal.h"
# include "./rt.h"

typedef enum			e_post_effect
{
	PP_SEPIA = 0,
	PP_CELL_SHADING,
	PP_NEGATIVE,
	PP_BLACK_WHITE,
	PP_BLUR,
	PP_MAX
}						t_post_effect;

void					apply_post_effect(t_cam *cam, t_post_effect e);

SDL_Surface				*ft_sepia(SDL_Surface *s);
SDL_Surface				*ft_cel_shading(SDL_Surface *s);
SDL_Surface				*ft_negative(SDL_Surface *s);
SDL_Surface				*ft_blackandwhite(SDL_Surface *s);
SDL_Surface				*ft_blur(SDL_Surface *s);

#endif
