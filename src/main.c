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
	//printf("%d\n",key);
	if (key == W)
		win->keys = 1.0;
	if (key == S)
		win->keys = -1.0;
	if (key == A)
		win->keys = -1.1;
	if (key == D)
		win->keys = 1.1;
	return 1;
}

int		key_release(int key, t_win *win)
{
	win->keys = 0.0;
	return 1;
}

int			mouse_hook(int x, int y, t_win *win)
{
	(void)y;	
	if ((WIDTH / 2 - x) > WIDTH / 4)
		win->mouse = 0.2;
	else if ((WIDTH / 2 - x) < - WIDTH / 4)
		win->mouse = -0.2;
	else
		win->mouse = 0;
	return 1;
}

//////////////////CHECK BORDER ON 0 IF(TRUE) REPLACE ON 1 OR WALL WITH INVIS
//////////////////THREADS  
///						1 thread - normal; >1 - destroy
//////////////////IF PRESSED TWO BUTTS kyes WILL BE 0 AFTER RLEASE ONLY ONE OF THEM
int		core(t_win *win)
{
	static int move = 1;
	if (move)
	{
		//display(win, 0, WIDTH);

		// display(win, 0, WIDTH_1_4);
		// display(win, WIDTH_1_4 * 2, WIDTH_1_4 * 3);

		thread_make(win);
		
		move = 0;
	}
	if (win->mouse != 0 || win->keys != 0.0)
	{
		mlx_destroy_image(win->mlx, win->env->newi);
		win->env->newi = mlx_new_image(win->mlx, WIDTH, HEIGHT);
		direction_win(win);
		position_win(win);
		display(win, 0, WIDTH);
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
