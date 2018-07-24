/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	txt_wallx(t_ray *ray, double dist)
{
	if (ray->wall == 0)
		ray->wallx = ray->pos.dy + dist * ray->dir.dy;
	else
		ray->wallx = ray->pos.dx + dist * ray->dir.dx;
	ray->wallx -= floor((ray->wallx));
	ray->t_x = I(ray->wallx * (float)TXT_W);
	if ((ray->wall == 0 && ray->dir.dx > 0) ||
		(ray->wall == 1 && ray->dir.dy < 0))
		ray->t_x = TXT_W - ray->t_x - 1;
}

void	txt_floor_direction(t_ray *ray)
{
	if (ray->wall == 0 && ray->dir.dx > 0)
	{
		ray->floor.dx = ray->pos.dx;
		ray->floor.dy = ray->pos.y + ray->wallx;
	}
	else if (ray->wall == 0 && ray->dir.dx < 0)
	{
		ray->floor.dx = ray->pos.x + 1.0;
		ray->floor.dy = ray->pos.y + ray->wallx;
	}
	else if (ray->wall == 1 && ray->dir.dy > 0)
	{
		ray->floor.dx = ray->pos.x + ray->wallx;
		ray->floor.dy = ray->pos.y;
	}
	else
	{
		ray->floor.dx = ray->pos.x + ray->wallx;
		ray->floor.dy = ray->pos.y + 1.0;
	}
}
