/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:20:00 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 13:20:02 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_map	*fill_map(char **line, int y)
{
	t_map		*map;
	t_map		*new;
	int			x;

	map = NULL;
	new = NULL;
	x = 0;
	if (line)
	{
		while (line[x])
		{
			if (map_valid_data(line[x]))
			{
				new = map_new_node(line[x], x, y);
				if (x == 0)
					new->first_in_row = 1;
				map_add_node(&map, new);
			}
			else
				ft_memdel((void **)&line[x]);
			x++;
		}
	}
	return (map);
}

static int		map_valid(char *line)
{
	int i;

	i = 0;
	if (line)
		while (line[i])
		{
			if ((line[0] != '0') && (line[0] != '1')
				&& (line[0] != ' ') && (line[0] != 'x'))
				return (0);
			i++;
		}
	return (1);
}

static t_map	*map_get_data(char *line)
{
	static t_map	*map = NULL;
	char			**splited_line;
	static int		entry = 0;

	if (line)
	{
		if (ft_strlen(line) > 0 && map_valid(line))
		{
			splited_line = ft_splinter(line, " \t");
			map_add_node(&map, fill_map(splited_line, entry));
			entry++;
			ft_memdel((void **)&splited_line);
		}
	}
	return (map);
}

t_map			*map_create(char *filename)
{
	t_map				*map;

	if (!filename)
		map_exception(map, "invalid file name");
	map = (t_map *)for_each_gnl(filename, (void *)&map_get_data);
	if (!map)
		map_exception(map, "NULL value");
	map_catch_exception(map);
	return (map);
}
