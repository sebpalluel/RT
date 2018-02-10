/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitequ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:07:34 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/19 13:14:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		ft_lines(char const *s, char *str)
{
	unsigned int		lines;
	unsigned int		i;
	int					flag;

	lines = 0;
	i = 0;
	flag = 0;
	while (s && s[i])
	{
		while (s[i] && ft_stroneof(s[i], str) == OK)
			i++;
		flag = 1;
		while (s[i] && ft_stroneof(s[i], str) != OK)
		{
			if (flag)
			{
				flag = 0;
				lines++;
			}
			i++;
		}
	}
	return (lines);
}

static unsigned int		ft_len(char const *s, char *str, int i)
{
	unsigned int		letters;

	letters = 0;
	while (s[i] && ft_stroneof(s[i], str) != OK)
	{
		letters++;
		i++;
	}
	return (letters);
}

char					**ft_strsplitequ(char const *s, char *str)
{
	char				**tmp;
	unsigned int		i;
	unsigned int		xy[2];

	i = 0;
	xy[1] = 0;
	if (!(tmp = (char**)malloc((ft_lines(s, str) + 1) * sizeof(char *))))
		return (NULL);
	while (s && s[i])
	{
		while (s[i] && ft_stroneof(s[i], str) == OK)
			i++;
		if (s[i])
		{
			xy[0] = 0;
			if (!(tmp[xy[1]] = malloc(sizeof(char) * ft_len(s, str, i) + 1)))
				return (NULL);
			while (s[i] && ft_stroneof(s[i], str) != OK)
				tmp[xy[1]][xy[0]++] = s[i++];
			tmp[xy[1]++][xy[0]] = '\0';
		}
	}
	tmp[xy[1]] = NULL;
	return (tmp);
}
