/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/13 15:01:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			write_line(t_str **current, char **target, int num_char)
{
	t_str			*prev;
	t_str			*buf;
	int				i;

	if (!(*target = ft_strnew(num_char)))
		return (READ_ERR);
	i = 0;
	buf = *current;
	while (buf && i != num_char)
	{
		(*target)[i] = buf->c;
		prev = buf;
		buf = buf->next;
		free(prev);
		i++;
	}
	if (buf)
	{
		*current = buf->next;
		free(buf);
	}
	else
		*current = NULL;
	return (READ_OK);
}

static int			get_line(t_str *buffer, int *num_char)
{
	*num_char = 0;
	while (buffer && buffer->c != '\n' && buffer->c != '\0')
	{
		(*num_char)++;
		buffer = buffer->next;
	}
	return (buffer ? 1 : 0);
}

static int			copy_buff(t_str **buffer, char *src)
{
	t_str			*current;

	if (*src && *buffer == NULL)
	{
		if (!(*buffer = (t_str *)ft_memalloc(sizeof(t_str))))
			return (READ_ERR);
		(*buffer)->c = *src;
		(*buffer)->next = NULL;
		src++;
	}
	current = *buffer;
	while (current && current->next)
		current = current->next;
	while (*src)
	{
		if (!(current->next = (t_str *)ft_memalloc(sizeof(t_str))))
			return (READ_ERR);
		current = current->next;
		current->c = *src;
		current->next = NULL;
		src++;
	}
	return (0);
}

static int			read_buff(t_str **buffer, int fd)
{
	char			src[BUFF_SIZE + 1];
	char			*get_line;
	int				ret;

	ret = BUFF_SIZE;
	get_line = NULL;
	while (!get_line && ret == BUFF_SIZE)
	{
		ft_bzero(src, BUFF_SIZE + 1);
		ret = read(fd, src, BUFF_SIZE);
		if (ret > 0 && copy_buff(buffer, src) == -1)
			return (READ_ERR);
		get_line = ft_strchr(src, '\n');
	}
	return (ret);
}

int					get_next_line(const int fd, char **line)
{
	static t_str	*fd_tab[OPEN_MAX] = {NULL};
	t_str			**buffer;
	int				num_char;
	int				ret;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFF_SIZE < 1)
		return (READ_ERR);
	buffer = &(fd_tab[fd]);
	if (!get_line(*buffer, &num_char))
	{
		ret = read_buff(buffer, fd);
		if (ret < 0)
			return (READ_ERR);
		if (ret == 0 && *buffer == NULL)
			return (READ_EOF);
	}
	get_line(*buffer, &num_char);
	return (write_line(buffer, line, num_char));
}
