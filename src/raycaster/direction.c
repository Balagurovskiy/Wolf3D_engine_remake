/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:01:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 18:01:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_xy	dir_rotate(t_xy dir, double vec)
{
	t_xy	new_dir;

	new_dir.dx = dir.dx * cos(vec * 0.1)
				- dir.dy * sin(vec * 0.1);
	new_dir.dy = dir.dx * sin(vec * 0.1)
				+ dir.dy * cos(vec * 0.1);
	return (new_dir);
}

t_xy	dir_plane(t_xy plane, double vec)
{
	t_xy	new_plane;

	new_plane.dx = plane.dx * cos(vec * 0.1)
				- plane.dy * sin(vec * 0.1);
	new_plane.dy = plane.dx * sin(vec * 0.1)
				+ plane.dy * cos(vec * 0.1);
	return (new_plane);
}

void	direction_win(t_win *win)
{
	int i;

	i = 0;
	win->dir = dir_rotate(win->dir, win->mouse);
	while (i < THREADS)
	{
		win->ray[i]->plane = dir_plane(win->ray[i]->plane, win->mouse);
		i++;
	}
}
