/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:06:29 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 13:06:32 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_map			*map_new_node(char *type, int x, int y)
{
	t_map	*new_node;

	new_node = (t_map*)malloc(sizeof(t_map));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->x = x;
	new_node->y = y;
	new_node->first_in_row = 0;
	new_node->next = NULL;
	return (new_node);
}

t_xy			map_get_xy(t_map *map, char type)
{
	t_map *m;

	if (map)
	{
		m = map;
		while (m)
		{
			if (m->type[0] == type)
				return (set_xy((double)m->x, (double)m->y));
			m = m->next;
		}
	}
	return (set_xy((double)1, (double)1));
}

char			map_get_type(t_map *map, int x, int y)
{
	t_map *m;

	if (map)
	{
		m = map;
		while (m)
		{
			if (m->x == x && m->y == y)
				return (m->type[0]);
			m = m->next;
		}
	}
	return ('0');
}

void			map_add_node(t_map **first_node, t_map *new_node)
{
	t_map *f;

	if (*first_node != NULL)
	{
		f = *first_node;
		while (f)
		{
			if (f->next == NULL)
			{
				f->next = new_node;
				break ;
			}
			f = f->next;
		}
	}
	else
		*first_node = new_node;
}

void			map_del_all(t_map **node)
{
	t_map *del;

	if (*node)
	{
		while (*node)
		{
			del = *node;
			*node = (*node)->next;
			ft_memdel((void **)&(del->type));
			free(del);
			del = NULL;
		}
	}
}

