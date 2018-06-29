/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:35:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/01/20 19:35:15 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_save(t_list *save, int fd)
{
	t_list *tmp;

	if (save)
	{
		tmp = save;
		while (tmp)
		{
			if (fd == (int)tmp->content_size)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

static void		make_save(t_list **save, char *after_n, int fd)
{
	t_list				*curr;

	if (ft_strlen(after_n) > 1)
	{
		curr = ft_lstnew(NULL, 0);
		curr->content = ft_strdup(after_n + 1);
		curr->content_size = fd;
		ft_list_add(save, curr);
	}
}

static int		return_gnl(char **line, t_list **save, char *after_n, int fd)
{
	char *temp;

	temp = NULL;
	if (HAS_N)
	{
		make_save(save, after_n, fd);
		temp = *line;
		*line = ft_strsub(temp, 0,
			(ft_strlen(*line) - ft_strlen(after_n)));
		ft_strdel(&temp);
	}
	return (1);
}

static void		read_loop(int fd, char **line, char *after_n)
{
	char		*temp;
	int			read_size;
	char		buff[BUFF_SIZE + 1];

	read_size = 0;
	while ((read_size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[read_size] = '\0';
		temp = *line;
		*line = ft_strjoin(*line, buff);
		ft_strdel(&temp);
		if (HAS_N)
			break ;
	}
}

int				get_next_line(const int fd, char **line)
{
	char				*after_n;
	static t_list		*save = NULL;
	t_list				*curr;

	curr = NULL;
	after_n = NULL;
	if (line == NULL || BUFF_SIZE <= 0 ||
		fd < 0 || read(fd, NULL, 0) < 0)
		return (-1);
	*line = NULL;
	if ((curr = get_save(save, fd)) != NULL)
	{
		*line = ft_strjoin(*line, curr->content);
		ft_lst_delone(&save, curr, &ft_list_clear);
	}
	read_loop(fd, line, after_n);
	if (*line)
		return (return_gnl(line, &save, after_n, fd));
	return (0);
}
