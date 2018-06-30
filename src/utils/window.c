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
	win->sky = NULL;
	win->env = NULL;
	win->map = NULL;
	win->keys = 0.0;
	win->mouse = 0.0;
	return (win);
}

void		window_map_init(t_win *win, char *map_file)
{	
	win->map = map_create(map_file);
	win->pos = map_get_xy(win->map, 'x');
	if (!win->map)
		window_exception(win, "NULL map");
}

void		window_ray_init(t_win *win)
{
	win->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!win->ray)
		window_exception(win, "raycast didnt malloced");
	win->dir = set_xy(1.0, 0.0);
	win->ray->plane = set_xy(0.0, -0.8);
}

void		window_destroy(t_win *w)
{
	if (w != NULL)
	{		
		if (w->ray != NULL)
			ft_memdel((void **)&(w->ray));
		if (w->map != NULL)
			map_del_all(&(w->map));
		if (w->sky != NULL)
			image_destroy(w->mlx, w->sky);
		if (w->env != NULL)
			image_destroy(w->mlx, w->env);
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