/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_scene.c                                         :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 17:20:12 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 16:22:30 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

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

size_t			ft_init_new_scene(t_scene *scn, const char *path)
{
	scn->move_step = MOVE_STEP;
	scn->rot_step = ROT_STEP;
	/*TODO expo and pers init for t_env
	  scn->pers = 1.;
	  scn->expo = 1.;
	  */
	if ((scn->fd = open(path, O_RDONLY, O_APPEND) > 0))
		return (OK);
	return (ERROR);
}

static char		*ft_append_line_to_file(t_scene *scn)
{
	char		*file;
	char		*line;
	char		*tmp;

	file = NULL;
	line = NULL;
	while (get_next_line(scn->fd, &line))
	{
		if (!line || (line && ft_checkascii(line) != OK))
		{
			scn->error = line ? SCN_ERROR : FILE_ERROR;
			return (NULL);
		}
		tmp = file;
		file = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	if (!file)
		scn->error = SCN_ERROR;
	return (file);
}

t_scene			*ft_open_scene(const char *path)
{
	char		*file;
	t_scene		*scn;

	scn = (t_scene*)ft_memalloc(sizeof(t_scene));
	if (!path || !scn || ft_init_new_scene(scn, path) != OK)
	{
		scn->error = FILE_ERROR;
		return (NULL);
	}
	if (!(file = ft_append_line_to_file(scn)))
		return (NULL);
	if (!(SCN.env = ft_parse_scn(scn, file)) || ft_envtosetup(scn) != OK\
			|| scn->error != OK)
		return (ERROR);
	if (SCN.num_cam == 0)
		return (scn->error = CAM_ERROR);
	SCN.cur_cam = CAM(SCN.cams);
	if (!scn->num_scn)
		scn->num_scn = 1;
	mlx_put_image_to_window(scn->mlx_ptr, UI_WIN->win_ptr, \
			UI_IMG->image, 0, 0);
	scn->mode = STATE_DRAW;
	return (OK);
}
