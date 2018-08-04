/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 14:18:13 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 14:18:15 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static	void	swap_0_to_1(char *type)
{
	if (type[0] != '1')
		type[0] = '1';
}

void			map_w_bordering(t_map *m)
{
	t_map		*map;
	int			count;

	map = m;
	count = 0;
	while (map)
	{
		if ((map->next && map->next->first_in_row)
			|| map->first_in_row)
			swap_0_to_1(map->type);
		count = map->x;
		map = map->next;
	}
}

void			map_h_bordering(t_map *m)
{
	t_map		*map;
	t_map		*f_in_row;

	map = m;
	while (map)
	{
		if (map->first_in_row == 1)
			f_in_row = map;
		if (map->x == 0 && map->y == 0)
			while (map->next && !map->next->first_in_row)
			{
				swap_0_to_1(map->type);
				map = map->next;
			}
		if (map->next == NULL)
			while (f_in_row)
			{
				swap_0_to_1(f_in_row->type);
				f_in_row = f_in_row->next;
			}
		map = map->next;
	}
}

void			map_check_x(t_map *m)
{
	t_xy check_pos;

	check_pos = map_get_xy(m, 'x');
	if (check_pos.dx < 0.0 || check_pos.dx < 0.0)
		map_exception(m, "invalid map content - insert <x>");
}
