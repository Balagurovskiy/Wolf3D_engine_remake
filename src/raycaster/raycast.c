/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:01:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 18:01:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ray_init(t_win *win, int x)
{
	// if (win->mouse != 0)
	// 	ft_rotate(win);
	win->ray->pos = set_xy(win->pos.dx, win->pos.dy);
	win->ray->camera = 2 * x / (double)(WIDTH) - 1;
	win->ray->dir = set_xy(win->dir.dx + win->ray->plane.dx * win->ray->camera, 
						win->dir.dy + win->ray->plane.dy * win->ray->camera);
	win->ray->delta = set_xy(fabs(1 / win->ray->dir.dx ),
						fabs(1 / win->ray->dir.dy ));


	
}

static void		ray_euclidean_distance(t_ray *ray)
{
	if (ray->dir.dx < 0)
	{
		ray->step.x = -1;
		ray->dist.dx = (ray->pos.dx - ray->pos.x) * ray->delta .dx;
	}
	else
	{
		ray->step.x = 1;
		ray->dist.dx = (ray->pos.x + 1.0 - ray->pos.dx) * ray->delta .dx;
	}
	if (ray->dir.dy < 0)
	{
		ray->step.y = -1;
		ray->dist.dy = (ray->pos.dy - ray->pos.y) * ray->delta .dy;
	}
	else
	{
		ray->step.y = 1;
		ray->dist.dy = (ray->pos.y + 1.0 - ray->pos.dy) * ray->delta .dy;
	}	
}

static void		ray_find_wall(t_ray *ray, t_map *map)
{
	char	map_type;
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->dist.dx < ray->dist.dy)
		{
			ray->dist.dx += ray->delta.dx;
			ray->pos.x += ray->step.x;
			ray->wall = 0;
		}
		else
		{
			ray->dist.dy += ray->delta.dy;
			ray->pos.y += ray->step.y;
			ray->wall = 1;
		}
		map_type = map_get_type(map, ray->pos.x, ray->pos.y);
		if (map_type != '0')
			hit = 1;
	}

}

static void		ray_size(t_win *win,t_ray *ray)
{
	double dist;

	if (ray->wall == 0)
		dist = fabs((ray->pos.x - ray->pos.dx
					+ (1 - ray->step.x) / 2) / ray->dir.dx);
	else
		dist = fabs((ray->pos.y - ray->pos.dy
					+ (1 - ray->step.y) / 2) / ray->dir.dy);
	ray->l_h = abs((int)(HEIGHT / dist));
	ray->l_start = (-1 * (ray->l_h)) / 2 + HEIGHT / 2;
	if (ray->l_start < 0)
		ray->l_start = 0;
	ray->l_end = ray->l_h / 2 + HEIGHT / 2;
	if (ray->l_end >= HEIGHT)
		ray->l_end = HEIGHT - 1;

	static int entry = 0;
		if (entry == 11)
	{
		printf("pos dx:%f dy:%f x:%d y:%d\n", win->ray->pos.dx,win->ray->pos.dy,win->ray->pos.x,win->ray->pos.y);
		printf("dir dx:%f dy%f\n", win->ray->dir.dx, win->ray->dir.dy);
		printf("delta dx:%f dy%f\n", win->ray->delta.dx, win->ray->delta.dy);
		printf("step dx:%d dy%d\n", win->ray->step.x,win->ray->step.y);
		printf("dist dx:%f dy%f\n", win->ray->dist.dx,win->ray->dist.dy);
		printf("start end dx:%d dy:%d rh:%d\n", win->ray->l_start,win->ray->l_end,win->ray->l_h);
	}
	entry++;
	if (entry == 1000)
		entry = 0;
}

void			raycast(t_win *win, int x)
{	
		ray_init(win, x);
		ray_euclidean_distance(win->ray);
		ray_find_wall(win->ray, win->map);
		ray_size(win,win->ray);
}
