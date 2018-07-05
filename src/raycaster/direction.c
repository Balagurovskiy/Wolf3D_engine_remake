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
	win->dir = dir_rotate(win->dir, win->mouse);
	win->ray->plane = dir_plane(win->ray->plane, win->mouse);
}
// void	dir_rotate(t_win *win)
// {
// 	double	dirx;
// 	double	planex;

// 	dirx = win->dir.dx;
// 	planex = win->ray->plane.dx;
// 	win->dir.dx = win->dir.dx * cos(win->mouse * 0.1)
// 		- win->dir.dy * sin(win->mouse * 0.1);
// 	win->dir.dy = dirx * sin(win->mouse * 0.1)
// 		+ win->dir.dy * cos(win->mouse * 0.1);
// 	win->ray->plane.dx = win->ray->plane.dx * cos(win->mouse * 0.1)
// 		- win->ray->plane.dy * sin(win->mouse * 0.1);
// 	win->ray->plane.dy = planex * sin(win->mouse * 0.1)
// 		+ win->ray->plane.dy * cos(win->mouse * 0.1);
// }