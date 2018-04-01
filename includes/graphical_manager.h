/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:57:34 by mbeilles          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/03/29 17:28:41 by mbeilles         ###   ########.fr       */
=======
/*   Updated: 2018/03/29 17:11:28 by psebasti         ###   ########.fr       */
>>>>>>> bf13c177fd8325d040d5a563cbab82d22e7954d7
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICAL_MANAGER_H
# define GRAPHICAL_MANAGER_H

# include "display_manager.h"
# include "kernal.h"
# include "rt.h"

<<<<<<< HEAD
=======
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

t_col					*ft_sepia(SDL_Surface *s, int x, int y);
t_col					*ft_cel_shading(SDL_Surface *s, int x, int y);
t_col					*ft_negative(SDL_Surface *s, int x, int y);
t_col					*ft_blackandwhite(SDL_Surface *s, int x, int y);
t_col					*ft_blur(SDL_Surface *s, int x, int y);
>>>>>>> bf13c177fd8325d040d5a563cbab82d22e7954d7

#endif
