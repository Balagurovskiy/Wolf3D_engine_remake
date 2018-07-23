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

static void		ray_init(t_win *win, int id, int x)
{
	win->ray[id]->pos = set_xy(win->pos.dx, win->pos.dy);
	win->ray[id]->camera = 2 * x / (double)(WIDTH) - 1;
	win->ray[id]->dir = set_xy(win->dir.dx + win->ray[id]->plane.dx * win->ray[id]->camera, 
						win->dir.dy + win->ray[id]->plane.dy * win->ray[id]->camera);
	win->ray[id]->delta = set_xy(fabs(1 / win->ray[id]->dir.dx ),
						fabs(1 / win->ray[id]->dir.dy ));
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
		if (map_type != '0' && map_type != 'x')
			hit = 1;
	}

}

static void		ray_wall_size(t_ray *ray)
{
	double dist;

	if (ray->wall == 0)
		dist = fabs((ray->pos.x - ray->pos.dx
					+ (1 - ray->step.x) / 2) / ray->dir.dx);
	else
		dist = fabs((ray->pos.y - ray->pos.dy
					+ (1 - ray->step.y) / 2) / ray->dir.dy);
	ray->l_h = abs(I(HEIGHT / dist));
	ray->l_start = (-1 * (ray->l_h)) / 2 + HEIGHT / 2;
	if (ray->l_start < 0)
		ray->l_start = 0;
	ray->l_end = ray->l_h / 2 + HEIGHT / 2;
	if (ray->l_end >= HEIGHT)
		ray->l_end = HEIGHT - 1;
	txt_wallx(ray, dist);
}

void			raycast(t_win *win, int thread_id, int x)
{	
		ray_init(win, thread_id, x);
		ray_euclidean_distance(win->ray[thread_id]);
		ray_find_wall(win->ray[thread_id], win->map);
		ray_wall_size(win->ray[thread_id]);
}
