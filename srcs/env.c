/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:33:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 17:33:27 by psebasti         ###   ########.fr       */
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

static t_list	*ft_newenv(char *str)
{
	t_list		*env; // changer env pour list parce que pas tres clair
	char		*tmp;

	if (!(env = (t_list*)malloc(sizeof(t_list))) || \
			!(env->content = (t_env*)ft_memalloc(sizeof(t_env))))
		return (NULL);
	env->content_size = sizeof(t_env);
	env->next = NULL;
	if (!(ENVSTRUCT(env)->name = ft_strsub(str, 0, ft_strchr(str, '=') - str)))
		return (NULL);
	tmp = ft_strchr(str, '=') + 1;
	if (!*tmp)
		ENVSTRUCT(env)->value = ft_strdup("");
	else
		ENVSTRUCT(env)->value = ft_strdup(tmp);
	return (env);
}

t_list			*ft_envlist(char **map_str) // fonction qui va permettre de stocker chaque ligne dans chaque chainons en bypassant les lignes vides
{
	int			env_num;
	t_list		*env;

	env = NULL;
	env_num = -1;
	while (map_str[++env_num])
	{
		if (map_str[env_num][0] != '\0') // bypass les lignes vides
			ft_lstaddend(&env, ft_newenv(map_str[env_num])); // chaque node contient le name (par exemple sphere) + la valeur (couleur etc.)
	}
	// a partir de l
	return (env);
}

char			**ft_getenv(t_setup *setup)
{
	char		**envtab;
	char		*str;
	int			i;
	t_list		*tmp;

	if (!(envtab = (char **)malloc(sizeof(char*) * (ft_lstlen(setup->env) + 1))))
		return (NULL);
	tmp = setup->env;
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
	char		*tmp;
	t_list		*list;

	if (name)
	{
		list = ft_searchenv(env, name);
		tmp = NULL;
		if (list == NULL)
		{
			tmp = ft_strjoin(name, "=");
			tmp = ft_strjoinfree(tmp, value, 1);
			ft_lstaddend(&env, ft_newenv(tmp));
			free(tmp);
		}
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
