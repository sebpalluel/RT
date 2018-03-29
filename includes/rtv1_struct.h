/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:32:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/29 15:59:47 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "../libft/includes/libft.h"
# include "./rtv1_define.h"

typedef struct		s_objsfunc
{
	size_t			(*builtinfunc)(void *a, t_list **list);
}					t_objsfunc;

typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef	struct		s_text
{
	t_col			*map;
	int				img_w;
	int				img_h;
}					t_text;

typedef	struct		s_text_c
{
	size_t			text_num;
	double			size_x;
	double			size_y;
}					t_text_c;

typedef	struct		s_gen
{
	size_t			mode;
	t_col			col;
	size_t			p_layers;
	double			p_f;
	double			p_prst;
}					t_gen;

#endif
