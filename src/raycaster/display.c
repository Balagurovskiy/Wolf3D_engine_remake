/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:01:20 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 18:01:22 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		draw_pixel(t_ray *ray,  int thr_id, t_xy xy, int color)
{
	if (out_of_range(thr_id, xy))
		return ;
	*(int *)(ray->env->addr + (xy.y * ray->env->sizel) +
			(get_thr_x(thr_id, xy.x) * (ray->env->bpp / 8))) = color;
}


static void		draw(t_ray *ray, int thr_id, int x)
{
	t_xy	xy;
	double	dist;

	xy.y = 0;
	xy.x = x;
	while (xy.y < ray->l_start)
	{
		draw_pixel(ray, thr_id, xy, 0xC00000A0);
		xy.y++;
	}
	while (xy.y >= ray->l_start && xy.y <= ray->l_end)
	{
		//draw_pixel(ray, thr_id, xy, ray->env->color);
		txt_draw_wall(ray, thr_id, xy);
		xy.y++;
	}
	txt_floor_direction(ray);
	dist = HEIGHT / ray->l_h;
	while (xy.y < HEIGHT)
	{
		//draw_pixel(ray, thr_id, xy, COLOR_FLOOR);
		txt_draw_floor(ray, thr_id, xy, dist);
		xy.y++;
	}
}

int		out_of_range(int thr_id, t_xy xy)
{
	int max_w;
	int min_w;

	max_w = I((WIDTH * 0.25) * (thr_id + 1));
	min_w = I((WIDTH * 0.25) * (thr_id));
	return (1);
}

int		get_thr_x(int thr_id, int x)
{
	return (1);
}

void			display(t_win *win, int thread_id, int x0, int xn)
{
	int		x;

	x = x0;
	while (x < xn)
	{
		raycast(win, thread_id, x);
		if (win->ray[thread_id]->wall == 0)
			win->ray[thread_id]->txt = (win->ray[thread_id]->step.x < 0
				? win->txts[0] : win->txts[1]);
		else
			win->ray[thread_id]->txt = (win->ray[thread_id]->step.y > 0
				? win->txts[2] : win->txts[3]);
		draw(win->ray[thread_id], thread_id, x);
		x++;
	}
}
