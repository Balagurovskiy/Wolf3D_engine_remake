/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:01:50 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 12:02:58 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_hit(int key, t_win *win)
{
	if (key == W || key == UP)
		win->movement.forward = 1.0;
	if (key == S || key == DOWN)
		win->movement.backward = -1.0;
	if (key == A)
		win->movement.step_left = -1.1;
	if (key == D)
		win->movement.step_right = 1.1;
	if ((win->sound_loop == 0 || win->sound_loop > 35) &&
		(key == D || key == A || key == S || key == W ||
			key == DOWN || key == UP))	
	{
		system("afplay ./music/Footsteps.mp3&");
		win->sound_loop = 0;
	}
	if (key == LEFT || key == RIGHT)
		win->mouse = (key == RIGHT) ? -MOUSE_SPEED : MOUSE_SPEED;
	else
		win->sound_loop++;
	if (key == ESC)
		window_destroy(win);
	return (1);
}

int		key_release(int key, t_win *win)
{
	if (key == W || key == UP)
		win->movement.forward = 0.0;
	if (key == S || key == DOWN)
		win->movement.backward = 0.0;
	if (key == A)
		win->movement.step_left = 0.0;
	if (key == D)
		win->movement.step_right = 0.0;
	if (key == D || key == A || key == S || key == W ||
		key == DOWN || key == UP)
		{	
			system("pkill afplay");
			win->sound_loop = 0;
		}
	if (key == LEFT || key == RIGHT)
		win->mouse = 0;
	return (1);
}

int			mouse_hook(int x, int y, t_win *win)
{
	(void)y;	
	if ((WIDTH / 2 - x) > WIDTH / 4)
		win->mouse = MOUSE_SPEED;
	else if ((WIDTH / 2 - x) < - WIDTH / 4)
		win->mouse = -MOUSE_SPEED;
	else
		win->mouse = 0;
	return (1);
}

int		core(t_win *win)
{
	static int move = 1;
	if (move)
	{
		thread_make(win);
		move = 0;
	}
	if (win->mouse || win->movement.forward || win->movement.backward
		|| win->movement.step_right || win->movement.step_left)
	{
		threads_reset_image(win);
		direction_win(win);
		position_win(win);
		thread_make(win);
		move = 1;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->sky->newi, 0, 0);
	threads_put_image(win);
	return (1);
}

int		main(int argc, char **argv)
{
	t_map				*map;
	t_win				*win;

	if (argc != 2)
		ft_putstr("\twolf3d usage : <executable> <map>");
	win = window_new(WIDTH, HEIGHT, "wolf3d");
	window_map_init(win, argv[1]);
	window_ray_init(win);	
	win->sky = image_new(win->mlx, WIDTH, HEIGHT, SKY_T);
	win->txts = txt_init(win->mlx);
	threads_set_image(win);
	mlx_hook(win->win, 17, 0, window_destroy, win);
	mlx_hook(win->win, 6, 0, mouse_hook, win);
	mlx_hook(win->win, 2, 0, key_hit, win);
	mlx_hook(win->win, 3, 0, key_release, win);
	mlx_loop_hook(win->mlx, core, win);
	mlx_loop(win->mlx);
	return (0);
}
