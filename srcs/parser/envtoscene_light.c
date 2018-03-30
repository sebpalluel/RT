/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:03:09 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 18:10:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

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

void			ft_light_struct_pop(t_list *lgt, t_list *env, t_bool *flag,
		size_t *num_arg)
{	
	if (ft_strcmp(P_ENV(env)->name, "type") == 0)
		flag[0] = ft_getsize_tfromenv(&LGT(lgt)->type, \
				P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "position") == 0)
		flag[1] = ft_getvectfromenv(&LGT(lgt)->vect, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&LGT(lgt)->col, P_ENV(env)->value);
		//if (LGT[NLIGHT].type && ft_strcmp(P_ENV(env)->name, "focal_len") == 0)
	//	flag[6] = ft_getdoublefromenv(&LGT[NLIGHT].focal_len, \
	//			P_ENV(env)->value);
	//if (LGT[NLIGHT].type && ft_strcmp(P_ENV(env)->name, "direction") == 0)
	//	flag[7] = ft_getvectfromenv(&LGT[NLIGHT].dir, P_ENV(env)->value);
	*num_arg += 1;
}

size_t			ft_light(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*lgt;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARLIGHT)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARLIGHT);
	ft_lstaddend(&scn->lgts, ft_newlgt());
	lgt = scn->lgts;
	while (lgt->next)
		lgt = lgt->next;
	num_arg = 0;
	while (num_arg < ((LGT(lgt)->type ? \
				NVARLIGHT : NVARLIGHT - 1)) && env && (env = env->next))
		ft_light_struct_pop(lgt, env, flag, &num_arg);
	if (ft_checkifallset(flag, num_arg) != OK)
		return (scn->error = LIGHT_ERROR);
	scn->num_lgt++;
	*list = env;
	return (OK);
}
