/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_lgt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 21:38:43 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_list	*ft_newlgt(void)
{
	t_list		*lgt;

	if (!(lgt = (t_list*)malloc(sizeof(t_list))) || \
			!(lgt->content = (t_lgt*)ft_memalloc(sizeof(t_lgt))))
		return (NULL);
	lgt->content_size = sizeof(t_lgt);
	lgt->next = NULL;
	return (lgt);
}

void			ft_light_struct_pop(t_list *lgt, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "type") == 0)
		flag[0] = ft_getsize_tfromenv(&LGT(lgt)->type, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "position") == 0)
		flag[1] = ft_getvectfromenv(&LGT(lgt)->vect, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&LGT(lgt)->col, ENVSTRUCT(env)->value);
	LGT(lgt)->num_arg++;
}

size_t			ft_light(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*lgt;
	t_bool		*flag;
	size_t		num_arg;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARLIGHT)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARLIGHT);
	ft_lstaddend(&SCN.lgts, ft_newlgt());
	lgt = SCN.lgts;
	while (lgt->next)
		lgt = lgt->next;
	while (LGT(lgt)->num_arg < (num_arg = (LGT(lgt)->type ? \
				NVARLIGHT : NVARLIGHT - 1)) && env && (env = env->next))
		ft_light_struct_pop(lgt, env, flag);
	if (ft_checkifallset(flag, num_arg) != OK)
		return (setup->error = LIGHT_ERROR);
	SCN.num_lgt++;
	*list = env;
	return (OK);
}
