/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:01:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 18:01:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		pos_is_it_floor(t_xy pos, t_xy dir, t_map *map, double keys)
{
	int		is_floor;
	char	map_type;
	int		x;
	int		y;

	x = (int)(pos.dx + keys * dir.dx * MOVE_SPEED * 2);
	y = (int)(pos.dy + keys * dir.dy * MOVE_SPEED * 2);
	map_type = map_get_type(map, x, y);
	return (map_type == '0' || map_type == 'x');
}

t_xy	pos_move(t_xy pos0, t_xy dir, double keys)
{
	t_xy pos;

	pos = pos0;
	pos.dx += keys * dir.dx * MOVE_SPEED;	
	pos.dy += keys * dir.dy * MOVE_SPEED;
	return (pos);
}

void	position_win(t_win *win)
{
	t_xy dir_temp;

	if (win->keys == 1.0 || win->keys == -1.0 )
		if (pos_is_it_floor(win->pos, win->dir, win->map, win->keys))
			win->pos = pos_move(win->pos, win->dir, win->keys);
	if (win->keys == 1.1 || win->keys == -1.1 )
	{
		dir_temp = win->dir;
		win->dir = dir_rotate(win->dir, (-(win->keys) * 14.5));
		if (pos_is_it_floor(win->pos, win->dir, win->map, 1.0))
			win->pos = pos_move(win->pos, win->dir, 1.0);
		win->dir = dir_temp;
	}
}

// void	action_step(t_win *win)
// {
// 	int		is_floor;
// 	char	map_type;
// 	int		x;
// 	int		y;

// 	if (win->keys != 1.1 && win->keys != -1.1 )
// 		return ;

// 	double	dirx;

// t_xy dir_save; dir_save.dx= win->dir.dx;dir_save.dy= win->dir.dy;

// 	// dirx = win->dir.dx; 
// 	// win->dir.dx = win->dir.dx * cos(-(win->keys / 2.0) * 16 * 0.1)
// 	// 	- win->dir.dy * sin(-(win->keys / 2.0) * 16 * 0.1);
// 	// win->dir.dy = dirx * sin(-(win->keys / 2.0) * 16 * 0.1)
// 	// 	+ win->dir.dy * cos(-(win->keys / 2.0) * 16 * 0.1);
// 	win->dir = dir_rotate(win->dir, (-(win->keys) * 16.0));

// 	x = (int)(win->pos.dx + win->dir.dx * MOVE_SPEED);
// 	y = (int)(win->pos.dy);
// 	map_type = map_get_type(win->map, x, y);
// 	is_floor = (map_type == '0' || map_type == 'x');
// 	if (is_floor)
// 		win->pos.dx += /*(win->keys / 2.0) **/ win->dir.dx * MOVE_SPEED;
// 	x = (int)(win->pos.dx);
// 	y = (int)(win->pos.dy + win->dir.dy * MOVE_SPEED);
// 	map_type = map_get_type(win->map, x, y);
// 	is_floor = (map_type == '0' || map_type == 'x');
// 	if (is_floor)
// 		win->pos.dy += /*(win->keys / 2.0) **/ win->dir.dy * MOVE_SPEED;

// 	win->dir.dx = dir_save.dx;win->dir.dy = dir_save.dy;
// }