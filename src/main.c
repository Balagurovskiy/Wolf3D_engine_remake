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
	if (key == W)
		win->keys = 1.0;
	if (key == S)
		win->keys = -1.0;
	if (key == A)
		win->keys = -2.0;
	if (key == D)
		win->keys = 2.0;
	return 1;
}

int		key_release(int key, t_win *win)
{
	win->keys = 0.0;
	return 1;
}

void	ft_move(t_win *win)
{
	int is_floor;
	int x;
	int y;

	x = (int)(win->pos.x + win->dir.dx * MOVE_SPEED);
	y = (int)(win->pos.y);
	is_floor = map_get_type(win->map, x, y) == '0';
		if (is_floor)
			win->pos.x += win->keys * win->pos.dx * MOVE_SPEED;
	x = (int)(win->pos.x);
	y = (int)(win->pos.y + win->dir.dy * MOVE_SPEED);
	is_floor = map_get_type(win->map, x, y) == '0';
		if (is_floor)
			win->pos.y += win->keys * win->pos.dy * MOVE_SPEED;
}

int			mouse_hook(int x, int y, t_win *win)
{
	(void)y;	
	if ((WIDTH / 2 - x) > WIDTH / 4)
		win->mouse = 0.5;
	else if ((WIDTH / 2 - x) < - WIDTH / 4)
		win->mouse = -0.5;
	else
		win->mouse = 0;
	return 1;
}

void 	thr(t_win *win)
{
	pthread_t		threads[4];
	int				idx;

	idx = 0;
	while (idx < 4)
	{
		pthread_create(&threads[idx], NULL,
			(void *(*)(void *))display,	(void *)win);
		idx++;
	}
	idx = 0;
	while (idx < 4)
		pthread_join(threads[idx++], NULL);
}

void	ft_rotate(t_win *win)
{
	double	dirx;
	double	planex;

	dirx = win->dir.dx;
	planex = win->ray->plane.dx;
	win->dir.dx = win->dir.dx * cos(win->mouse * 0.1)
		- win->dir.dy * sin(win->mouse * 0.1);
	win->dir.dy = dirx * sin(win->mouse * 0.1)
		+ win->dir.dy * cos(win->mouse * 0.1);
	win->ray->plane.dx = win->ray->plane.dx * cos(win->mouse * 0.1)
		- win->ray->plane.dy * sin(win->mouse * 0.1);
	win->ray->plane.dy = planex * sin(win->mouse * 0.1)
		+ win->ray->plane.dy * cos(win->mouse * 0.1);
}

int		core(t_win *win)
{
	
	// thr(win);

	static int move = 1;
	if (move)
	{
			display(win);
			move = 0;
	}
	if (win->mouse != 0)
	{
		mlx_destroy_image(win->mlx, win->env->newi);
		win->env->newi = mlx_new_image(win->mlx, WIDTH, HEIGHT);
		ft_rotate(win);
		ft_move(win);
		display(win);
		move = 1;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->sky->newi, 0, 0);
	mlx_put_image_to_window(win->mlx, win->win, win->env->newi, 0, 0);
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
	win->env = image_new(win->mlx, WIDTH, HEIGHT, NULL);
	win->sky = image_new(win->mlx, WIDTH, HEIGHT, SKY_T);	

	mlx_hook(win->win, 6,0, mouse_hook, win);
	mlx_hook(win->win, 2, 0, key_hit, win);
	mlx_hook(win->win, 3, 0, key_release, win);
	mlx_loop_hook(win->mlx, core, win);

	mlx_loop(win->mlx);
	return (0);
}
