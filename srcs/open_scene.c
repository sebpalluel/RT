/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:56:29 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 17:19:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t			ft_envtosetup(t_setup *setup)
{
	t_list		*env;
	int			i;
	t_bool		flag;

	env = SCN.env;
	while (env && ENV(env))
	{
		i = -1;
		flag = ERROR;
		while (env && ++i < NUM_OBJS)
		{
			if (ft_strcmp(ENV(env)->name, ft_validobjs()[i]) == 0)
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
	else if (scene == 2)
		setup->path = ft_strdup(SCN_PATH_2);
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
		if (!line)
			return (NULL);
		tmp = file;
		file = ft_strjoin(tmp, line);
		free(tmp);
	}
	return (file);
}

size_t			ft_open_scene(t_setup *setup)
{
	char		*file;

	if (ft_init_new_scene(setup) != OK || \
			ft_open(&SCN.fd, O_RDONLY, O_APPEND) != OK)
		return (setup->error = FILE_ERROR);
	if (!(file = ft_append_line_to_file(setup)))
		return (setup->error = FILE_ERROR);
	if (!(SCN.env = ft_parse_scn(setup, file)) || ft_envtosetup(setup) != OK\
			|| setup->error != OK)
		return (ERROR);
	if (SCN.num_cam == 0)
		return (setup->error = CAM_ERROR);
	if (!setup->num_scn)
		setup->num_scn = 1;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	setup->mode = STATE_DRAW;
	return (OK);
}
