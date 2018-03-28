/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_scene.c                                         :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 17:20:12 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/28 17:56:32 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t			ft_envtosetup(t_setup *setup)
{
	t_list		*env;
	int			i;
	t_bool		flag;
	char		**validobjs;

	env = SCN.env;
	validobjs = ft_validobjs();
	while (env && ENVSTRUCT(env))
	{
		i = -1;
		flag = ERROR;
		while (env && ++i < NUM_OBJS)
		{
			if (ft_strcmp(ENVSTRUCT(env)->name, validobjs[i]) == 0)
			{

				flag = OK;
				if (parse_obj()[i](&env) != OK)
					return (ERROR);
				if (env)
					env = env->next;
			}
		}
		if (flag == ERROR)
			return (ERROR);
	}
	return (OK);
}

size_t			ft_select_scene(t_setup *setup, int scene)
{
	if (setup->path)
		ft_strdel(&setup->path);
	if (scene == 0)
		setup->path = ft_strdup(SCN_PATH_0);
	else if (scene == 1)
		setup->path = ft_strdup(SCN_PATH_1);
	if (setup->path != NULL)
		return (OK);
	else
		return (ERROR);
}

size_t			ft_init_new_scene(t_setup *setup)
{
	ft_args_to_fd(setup);
	SCN.move_step = MOVE_STEP;
	SCN.rot_step = ROT_STEP;
	SCN.pers = 1.;
	SCN.expo = 1.;
	return (OK);
}

static char		*ft_append_line_to_file(t_setup *setup)
{
	char		*file;
	char		*line;
	char		*tmp;

	file = NULL;
	line = NULL;
	while (get_next_line(SCN.fd.fd, &line))
	{
		if (!line || (line && ft_checkascii(line) != OK))
		{
			setup->error = line ? SCN_ERROR : FILE_ERROR;
			return (NULL);
		}
		tmp = file;
		file = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	if (!file)
		setup->error = SCN_ERROR;
	return (file);
}

size_t			ft_open_scene(t_setup *setup)
{
	char		*file;

	if (ft_init_new_scene(setup) != OK || \
			ft_open(&SCN.fd, O_RDONLY, O_APPEND) != OK)
		return (setup->error = FILE_ERROR);
	if (!(file = ft_append_line_to_file(setup)))
		return (setup->error);
	if (!(SCN.env = ft_parse_scn(setup, file)) || ft_envtosetup(setup) != OK\
			|| setup->error != OK)
		return (ERROR);
	if (SCN.num_cam == 0)
		return (setup->error = CAM_ERROR);
	SCN.cur_cam = CAM(SCN.cams);
	if (!setup->num_scn)
		setup->num_scn = 1;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	setup->mode = STATE_DRAW;
	return (OK);
}
