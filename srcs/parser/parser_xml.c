/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_xml.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:07:04 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 22:09:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		ft_movescope(char **str, size_t len)
{
	char		*trunc_str;
	char		*tmp;

	tmp = *str;
	trunc_str = ft_strnew(ft_strlen(*str) - len);
	ft_memcpy(trunc_str, &str[0][len], ft_strlen(*str) - len);
	*str = trunc_str;
	ft_strdel(&tmp);
}

static void		ft_free(char *objstart, char *objend)
{
	if (objstart)
		ft_strdel(&objstart);
	if (objend)
		ft_strdel(&objend);
}

static char		*ft_extractobj(size_t len, char *from_begin, char *from_end)
{
	char		*objstr;

	if (from_end - (from_begin + len + 1) > 0)
	{
		if (!(objstr = ft_strnew(from_end - (from_begin + len) + 1)))
			return (NULL);
		ft_strncpy(objstr, from_begin + len, from_end - (from_begin + len));
		return (objstr);
	}
	return (NULL);
}

char			*ft_getobjstr(char *str, char *obj)
{
	char		*objstart;
	char		*objend;
	char		*from_begin;
	char		*from_end;
	char		*objstr;

	objstr = NULL;
	from_begin = NULL;
	from_end = NULL;
	objstart = ft_strjoinfree(ft_strdup("<"), ft_strjoin(obj, ">"), 0);
	objend = ft_strjoinfree(ft_strdup("</"), ft_strjoin(obj, ">"), 0);
	if (objstart && objend)
	{
		if (!(from_begin = ft_strstr(str, objstart)) || \
				!(from_end = ft_strstr(from_begin, objend)))
		{
			ft_free(objstart, objend);
			return (NULL);
		}
		objstr = ft_extractobj(ft_strlen(objstart), from_begin, from_end);
	}
	ft_free(objstart, objend);
	return (objstr);
}

char			*ft_getobjstrn(char **str, char *obj)
{
	char		*objstart;
	char		*objend;
	char		*from_begin;
	char		*from_end;
	char		*objstr;

	objstr = NULL;
	from_begin = NULL;
	from_end = NULL;
	objstart = ft_strjoinfree(ft_strdup("<"), ft_strjoin(obj, ">"), 0);
	objend = ft_strjoinfree(ft_strdup("</"), ft_strjoin(obj, ">"), 0);
	if (objstart && objend)
	{
		if (!(from_begin = ft_strstr(*str, objstart)) || \
				!(from_end = ft_strstr(from_begin, objend)))
		{
			ft_free(objstart, objend);
			return (NULL);
		}
		objstr = ft_extractobj(ft_strlen(objstart), from_begin, from_end);
		ft_movescope(str, from_end - *str);
	}
	ft_free(objstart, objend);
	return (objstr);
}
