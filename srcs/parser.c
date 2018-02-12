/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:14:30 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/12 19:14:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

char			*ft_get_matching_end(char *str, char *objstart,
				char *objend)
{
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (ft_strncmp(str + i, objstart, ft_strlen(objstart)) == OK)
			count++;
		if (ft_strncmp(str + i, objend, ft_strlen(objend)) == OK)
		{
			if (count != 0)
				count--;
			else
				return (str + i);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_inner(size_t len, char *ptr[2])
{
	char	*ret;

	if (ptr[1] - (ptr[0] + len + 1) >= 0)
	{
		if ((ret = malloc(ptr[1] - (ptr[0] + len) + 1)) == NULL)
			exit(-1);
		ft_strncpy(ret, ptr[0] + len, ptr[1] - (ptr[0] + len));
		ret[ptr[1] - (ptr[0] + len)] = '\0';
		return (ret);
	}
	return (NULL);
}

char		*ft_get_inner(char *str, char *obj)
{
	char	*objstart;
	char	*objend;
	char	*ptr[2];
	char	*ret;

	ret = NULL;
	objstart = ft_strjoinfree(ft_strdup("<"), ft_strjoin(obj, ">"), 0);
	printf("objstart : %s\n", objstart);
	objend = ft_strjoinfree(ft_strdup("</"), ft_strjoin(obj, ">"), 0);
	printf("objend : %s\n", objend);
	if ((ptr[0] = ft_strstr(str, objstart)) != NULL
		&& (ptr[1] = ft_get_matching_end(ptr[0] + 1,
			objstart, objend)) != NULL)
		ret = ft_inner(ft_strlen(objstart), ptr);
	ft_strdel(&objstart);
	ft_strdel(&objend);
	return (ret);
}

void		ft_parse_scn(t_setup *setup, char *file)
{
	char	*scene;
	char	*cameras;
	//char	*lights;
	//char	*objects;
	//char	*config;
	if (!(scene = ft_get_inner(file, "scene")))
		SETUP.error = SCN_ERROR;
	printf("scene :\n%s\n", scene);
	if ((cameras = ft_get_inner(scene, "cameras")) == NULL)
		SETUP.error = CAM_ERROR;
	printf("cameras :\n%s\n", cameras);
	//if ((config = ft_get_inner(scene, "config")) == NULL)
	//	ft_error_exit(ERR_NO_CONFIG);
	//if ((objects = ft_get_inner(scene, "objects")) == NULL)
	//	ft_putstr("There are no objects in your scene file.\n");
	//((lights = ft_get_inner(scene, "lights")) != NULL) ?
	//	ft_get_lights(lights, ft_strlen(lights), e) :
	//	ft_putstr("There are no lights in your scene file.\n");
	//ft_set_config(config, e);
	//ft_set_camera(camera, e);
	//ft_set_objects(objects, e);
	//ft_free_all_dat_stuff((char **[5]){&lights, &scene, &camera, &objects,
	//										&config});
}
