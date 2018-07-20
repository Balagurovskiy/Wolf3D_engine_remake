/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 14:18:13 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 14:18:15 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					map_valid_data(char *data)
{
	int i;

	i = 0;
	if (data)
		while (data[i])
			i++;
	if (i > 1)
		return (0);
	return ((data[0] >= '0' && data[0] <= '9') || data[0] == 'x');
}


static int			different_line_size(t_map	*m, int size)
{
	t_map		*map;
	int			count;

	
	map = m;
	count = 0;
	while (map)
	{
		if (map->first_in_row && count > 0)
		{
			if (count != size)
				return (1);
		}
		count = map->x;
		map = map->next;
	}
	return (0);
}

int					map_catch_exception(t_map	*m)
{
	t_map		*map;
	int			count;

	if (!m)
		map_exception(m, "NULL value");
	map = m;
	count = 0;
	while (map)
	{
		if (map->first_in_row && count > 0)
		{
			if (different_line_size(m, count))
				map_exception(m, "invalid size");
		}
		count = map->x;
		map = map->next;
	}
	return (0);
}

void				map_exception(t_map	*m, char *msg)
{
	ft_putstr("\tmap exception : ");
	ft_putstr(msg);
	write(1, "\n", 1);
	map_del_all(&m);
	exit(1);
}
