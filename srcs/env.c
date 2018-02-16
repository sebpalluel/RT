/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:33:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 16:50:58 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_list			*ft_searchenv(t_list *env, char *name)
{
	t_list		*list;

	list = env;
	if (name)
		while (list)
		{
			if (ENVSTRUCT(list) && ft_strcmp(name, ENVSTRUCT(list)->name) == OK)
				return (list);
			list = list->next;
		}
	return (NULL);
}

t_list			*ft_newenv(char *name, char *value)
{
	t_list		*env; // changer env pour list parce que pas tres clair

	if (!(env = (t_list*)malloc(sizeof(t_list))) || \
			!(env->content = (t_env*)ft_memalloc(sizeof(t_env))))
		return (NULL);
	env->content_size = sizeof(t_env);
	env->next = NULL;
	ENVSTRUCT(env)->name = name;
	if (value)
		ENVSTRUCT(env)->value = value;
	else
		ENVSTRUCT(env)->value = ft_strdup("");
	if (!ENVSTRUCT(env)->name || !ENVSTRUCT(env)->value)
		return (NULL);
	return (env);
}

char			**ft_getenv(t_setup *setup)
{
	char		**envtab;
	char		*str;
	int			i;
	t_list		*tmp;

	if (!(envtab = (char **)malloc(sizeof(char*) * (ft_lstlen(SCN.env) + 1))))
		return (NULL);
	tmp = SCN.env;
	i = 0;
	while (tmp)
	{
		str = ft_strdup(ENVSTRUCT(tmp)->name);
		str = ft_strjoinfree(str, "=", 1);
		str = ft_strjoinfree(str, ENVSTRUCT(tmp)->value, 1);
		envtab[i++] = ft_strdup(str);
		free(str);
		tmp = tmp->next;
	}
	envtab[i] = NULL;
	return (envtab);
}

void			ft_editenv(t_list *env, char *name, char *value)
{
	t_list		*list;

	if (name)
	{
		list = ft_searchenv(env, name);
		if (list == NULL)
			ft_lstaddend(&env, ft_newenv(name, value));
		else
		{
			free(ENVSTRUCT(list)->value);
			if (value)
				ENVSTRUCT(list)->value = ft_strdup(value);
			else
				ENVSTRUCT(list)->value = ft_strdup("");
		}
	}
}
