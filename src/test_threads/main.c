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
#include "map.h"

int		core(t_win *win)
{
	static int thread_idx = 0;

	printf("core 0 [%d]\n", thread_idx);
	//mlx_destroy_image(win->mlx, win->env[thread_idx]->newi);
	win->env[thread_idx]->newi = mlx_new_image(win->mlx, WIDTH_1_4, HEIGHT);
	printf("core I [%d]\n", thread_idx);
	//mlx_put_image_to_window(win->mlx, win->win, win->sky->newi, 0, 0);
	int y = 0;
	while (y < HEIGHT)
	{
		int x = WIDTH_1_4 * (float)thread_idx;
		while (x < WIDTH_1_4 * (float)(thread_idx + 1.0))
		{
			*(int *)(win->env[thread_idx]->addr + (int)((y + x * WIDTH_1_4) * win->env[thread_idx]->bpp)) = 0xffff + thread_idx;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->env[thread_idx]->newi,
							WIDTH_1_4 * (float)thread_idx, 0);
	printf("core II [%d]\n", thread_idx);
	thread_idx++;
	if (thread_idx >= THREADS)
		thread_idx = 0;
	return (1);
}

int		run_threads(t_win *win)
{
	pthread_t		threads[THREADS];
	int				idx;

	idx = 0;
	while (idx < THREADS)
	{printf(".\n");
		pthread_create(&threads[idx], NULL, (void *(*)(void *))core,
						(void *)win);
		printf("threads created %d\n", idx);
		idx++;
	}
	idx = 0;
	while (idx < THREADS)
		{pthread_join(threads[idx++], NULL);printf("threads loaded %d\n", idx);}
	return (1);
}

int		main(int argc, char **argv)
{
	t_map				*map;
	t_win				*win;

	if (argc != 2)
		return (0);
	//map = map_create(argv[1]);	
/*----------------------------------*/
//destructors needed
	
	win = NULL;
	win = (t_win *)malloc(sizeof(t_win));
	if (!win)
		exit(1);
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "wolf3d");


	win->env = NULL;
	win->env = (t_img **)malloc(sizeof(t_img *) * THREADS);
	if (!win->env)
		exit(1);

	int i = 0;
	while (i < THREADS)
	{
		win->env[i] = NULL;
		win->env[i] = (t_img *)malloc(sizeof(t_img));
		if (!win->env[i])
			exit(1);
		win->env[i]->newi = mlx_new_image(win->mlx, WIDTH_1_4, HEIGHT);
		win->env[i]->addr = mlx_get_data_addr(win->env[i]->newi, &win->env[i]->bpp, 
							&win->env[i]->sizel, &win->env[i]->endi);
		i++;
	}

	win->sky = NULL;
	win->sky = (t_img *)malloc(sizeof(t_img));
	if (!win->sky)
		exit(1);
	int width = WIDTH;
	int height = HEIGHT / 2;
	win->sky->newi = mlx_xpm_file_to_image(win->mlx,  "textures/sky.xpm", &width, &height);
	win->sky->addr = mlx_get_data_addr(win->sky->newi, &win->sky->bpp, 
						&win->sky->sizel, &win->sky->endi);
	mlx_put_image_to_window(win->mlx, win->win, win->sky->newi, 0, 0);



	//mlx_loop_hook(win->mlx, run_threads, win); ///core --> thread
	run_threads(win);
	mlx_loop(win->mlx);
	return (0);
}

// 	int y = 0;
// 	while (map)
// 	{
// 		if (y != map->y)
// 			printf("\n");

// 		printf("{[%s ",map->type);
// 		printf(" %d] ",map->first_in_row);
// 		printf("%d|",map->x);
// 		printf("%d}",map->y);
// 		y = map->y;
// 		map = map->next;
// 	}
// // while(1);