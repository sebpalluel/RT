/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_manager.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:57:34 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/31 17:01:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICAL_MANAGER_H
# define GRAPHICAL_MANAGER_H

# include "display_manager.h"
# include "kernal.h"
# include "rt.h"

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
