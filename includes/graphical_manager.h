/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:57:34 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/31 17:07:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICAL_MANAGER_H
# define GRAPHICAL_MANAGER_H

# include "display_manager.h"
# include "kernal.h"
# include "rt.h"

/*
** =============================================================================
** 						Post proccess
** =============================================================================
*/

typedef enum	e_post_effect
{
	PP_SEPIA = 0,
	PP_CELL_SHADING,
	PP_NEGATIVE,
	PP_BLACK_WHITE,
	PP_BLUR,
	PP_MAX
}				t_post_effect;

/*
** =============================================================================
** 							Function typedefs
** =============================================================================
*/

typedef t_col	(*t_postproc)();

/*
** =============================================================================
** 							Function prototypes
** =============================================================================
*/

t_col			ft_sepia(SDL_Surface *s, int x, int y);
t_col			ft_blur(SDL_Surface *s, int x, int y);
t_col			ft_cel_shading(SDL_Surface *s, int x, int y);
t_col			ft_blackandwhite(SDL_Surface *s, int x, int y);
t_col			ft_negative(SDL_Surface *s, int x, int y);
t_col			ft_effect_change(SDL_Surface *s, int x, int y);
t_postproc		*postprocess(void);


#endif
