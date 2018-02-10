/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 21:01:20 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/25 11:25:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	custom(char *command, char *tmp, char *file_path, int mode)
{
	char *tmp2;

	tmp2 = NULL;
	if (mode)
	{
		tmp2 = ft_strjoin(tmp, file_path);
		command = ft_strjoin("chmod ", tmp2);
		free(tmp2);
	}
	system(command);
	free(command);
	if (tmp != NULL)
		free(tmp);
	if (file_path != NULL)
		free(file_path);
}

size_t		ft_create_file(t_fd *fd, int chmod)
{
	char	*file_path;
	char	*command;
	char	*tmp;
	char	*tmp_num;
	int		len;

	file_path = ft_strjoin(fd->path, fd->name);
	command = ft_strjoin("touch ", file_path);
	if (file_path == NULL && command == NULL)
		return (ERROR);
	else
		custom(command, NULL, NULL, 0);
	tmp_num = ft_itoa(chmod);
	len = ft_strlen(tmp_num);
	tmp = ft_strdup(tmp_num);
	free(tmp_num);
	tmp_num = ft_straddchar(tmp, ' ');
	free(tmp);
	if (tmp_num == NULL && command == NULL)
		return (ERROR);
	else
		custom(command, tmp_num, file_path, 1);
	return (OK);
}
