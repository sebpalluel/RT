/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:35:51 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 19:15:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		ft_lines(char const *s, char c)
{
	unsigned int	lines;
	unsigned int	i;
	int				flag;

	lines = 0;
	i = 0;
	flag = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == (char)c)
			i++;
		flag = 1;
		while (s[i] && s[i] != (char)c)
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

static unsigned int		ft_letters(char const *s, char c, int i)
{
	unsigned int	letters;

	letters = 0;
	while (s[i] != c && s[i])
	{
		letters++;
		i++;
	}
	return (letters);
}

char					**ft_strsplit(char const *s, char c)
{
	char			**tmp;
	unsigned int	i;
	unsigned int	lines;
	unsigned int	letters;

	i = 0;
	lines = 0;
	if (!(tmp = (char**)malloc((ft_lines(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (s && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			letters = 0;
			if (!(tmp[lines] = malloc(sizeof(char) * ft_letters(s, c, i) + 1)))
				return (NULL);
			while (s[i] != c && s[i])
				tmp[lines][letters++] = s[i++];
			tmp[lines++][letters] = '\0';
		}
	}
	tmp[lines] = NULL;
	return (tmp);
}
