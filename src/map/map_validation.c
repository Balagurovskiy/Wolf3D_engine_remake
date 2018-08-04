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
	return (data[0] == '0' || data[0] == '1'
		|| data[0] == ' ' || data[0] == 'x');
}

static int			too_big(void)
{
	static int limit = 0;

	limit++;
	if (limit > 3000)
		return (1);
	return (0);
}

int					map_catch_exception(t_map *m)
{
	t_map		*map;
	int			count_all;
	int			count_lines;

	map = m;
	count_all = 0;
	count_lines = 0;
	while (map)
	{
		if (map->first_in_row)
			count_lines++;
		count_all++;
		map = map->next;
	}
	if (!count_lines)
		map_exception(m, "file is empty");
	if (count_all % count_lines != 0 || too_big())
		map_exception(m, "invalid size");
	map_w_bordering(m);
	map_h_bordering(m);
	map_check_x(m);
	return (0);
}

void				map_exception(t_map *m, char *msg)
{
	ft_putstr("\tmap exception : ");
	ft_putstr(msg);
	write(1, "\n", 1);
	map_del_all(&m);
	exit(1);
}
