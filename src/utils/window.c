/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:40:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 13:40:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_win		*window_new(int w, int h, char *name)
{
	t_win	*win;

	win = NULL;
	win = (t_win *)malloc(sizeof(t_win));
	if (!win)
		window_exception(win, "window didnt malloced");
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, w, h, name);
	win->dir = set_xy(1.0, 0.0);
	win->sky = NULL;
	win->map = NULL;
	win->mouse = 0.0;
	return (win);
}

void		window_map_init(t_win *win, char *map_file)
{
	win->map = map_create(map_file);
	win->pos = map_get_xy(win->map, 'x');
	win->pos = set_xy(win->pos.dx + 0.5, win->pos.dy + 0.5);
	if (!win->map)
		window_exception(win, "NULL map");
	win->movement.forward = 0.0;
	win->movement.backward = 0.0;
	win->movement.step_left = 0.0;
	win->movement.step_right = 0.0;
}

void		window_ray_init(t_win *win)
{
	int i;

	i = 0;
	win->ray = NULL;
	win->ray = (t_ray **)malloc(sizeof(t_ray *) * THREADS);
	if (!win->ray)
		window_exception(win, "raycast didnt malloced");
	while (i < THREADS)
	{
		win->ray[i] = NULL;
		win->ray[i] = (t_ray *)malloc(sizeof(t_ray));
		if (!win->ray[i])
			window_exception(win, "raycast didnt malloced");
		win->ray[i]->plane = set_xy(0.0, -0.8);
		i++;
	}
}

void		window_destroy(t_win *w)
{
	int i;

	i = 0;
	if (w != NULL)
	{
		threads_free_image(w);
		txt_free(w->mlx, w->txts);
		while ((w->ray != NULL) && (i < THREADS))
			if (w->ray[i] != NULL)
				ft_memdel((void **)&(w->ray[i++]));
		if (w->ray != NULL)
			ft_memdel((void **)&(w->ray));
		if (w->map != NULL)
			map_del_all(&(w->map));
		if (w->sky != NULL)
			image_destroy(w->mlx, w->sky);
		if (w->win != NULL)
			mlx_destroy_window(w->mlx, w->win);
		ft_memdel((void **)&w);
	}
}

void		window_exception(t_win *win, char *msg)
{
	ft_putstr("\twindow exception : ");
	ft_putstr(msg);
	write(1, "\n", 1);
	window_destroy(win);
	exit(1);
}
