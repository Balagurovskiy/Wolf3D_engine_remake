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

int		out_of_range(int thr_id, t_xy xy)
{
	int max_w;
	int min_w;

	max_w = I(WIDTH_1_4 * (thr_id + 1));
	min_w = I(WIDTH_1_4 * (thr_id));

	return (xy.y >= HEIGHT || xy.y < 0
			|| xy.x >=  max_w || xy.x < min_w);
}

int		get_thr_x(int thr_id, int x)
{
	return (x - I(WIDTH_1_4 * (thr_id)));
}

static void		draw_pixel(t_ray *ray,  int thr_id, t_xy xy, int color)
{
	if (out_of_range(thr_id, xy))
		return ;
	*(int *)(ray->env->addr + (xy.y * ray->env->sizel) +
			(get_thr_x(thr_id, xy.x) * (ray->env->bpp / 8))) = color;
}


static void		draw(t_ray *ray, int thr_id, int x)
{
	t_xy xy;

	xy.y = 0;
	xy.x = x;
	// printf("===1===%d=%d   [%d]\n",xy.x ,xy.y ,thr_id);
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
	while (xy.y < HEIGHT)
	{
		//draw_pixel(ray, thr_id, xy, COLOR_FLOOR);
		txt_draw_floor(ray, thr_id, xy);

		xy.y++;
	}
}

void test(t_win *win, int i);
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
	//test(win, thread_id);
}

void test(t_win *win, int i)
{

	// static int entry = 0;
	// 	if (entry == 11)
	// {
		printf("pos dx:%f dy:%f x:%d y:%d\n", win->ray[i]->pos.dx,win->ray[i]->pos.dy,win->ray[i]->pos.x,win->ray[i]->pos.y);
		printf("Rdir dx:%f dy%f\n", win->ray[i]->dir.dx, win->ray[i]->dir.dy);
		printf("plane dx:%f dy%f\n", win->ray[i]->plane.dx, win->ray[i]->plane.dy);
		printf("dir dx:%f dy%f\n ", win->dir.dx, win->dir.dy);
		printf("delta dx:%f dy%f\n", win->ray[i]->delta.dx, win->ray[i]->delta.dy);
		printf("step dx:%d dy%d\n", win->ray[i]->step.x,win->ray[i]->step.y);
		printf("dist dx:%f dy%f\n", win->ray[i]->dist.dx,win->ray[i]->dist.dy);
		printf("start end dx:%d dy:%d rh:%d\n\n", win->ray[i]->l_start,win->ray[i]->l_end,win->ray[i]->l_h);
	// }
	// entry++;
	// if (entry == 1000)
	// 	entry = 0;
}
