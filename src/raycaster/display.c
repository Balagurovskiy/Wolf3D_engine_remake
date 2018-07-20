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

static int		out_of_range(int thr_id, t_xy xy)
{
	int max_w;
	int min_w;

	max_w = I(WIDTH_1_4 * (thr_id + 1));
	min_w = I(WIDTH_1_4 * (thr_id));

	return (xy.y >= HEIGHT || xy.y < 0
			|| xy.x >=  max_w || xy.x < min_w);
}

static int		get_thr_x(int thr_id, int x)
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


static void		draw_texture(t_ray *ray, int thr_id, t_xy xy, char *type)
{
	int				d;
	t_color			color;
	int 			txt_addr_idx;
	int 			env_addr_idx;

 	if (out_of_range(thr_id, xy))
		return ;
	d = xy.y * 256 - HEIGHT * 128 + ray->l_h * 128;
	ray->t_y = ((d * 64 / ray->l_h) / 256);
	txt_addr_idx = I(4 * (64 * ray->t_y + ray->t_x));
	if (!ft_strcmp(type, "wall"))
		color = color_get_pixel(ray->txt->addr, txt_addr_idx);
	if (!ft_strcmp(type, "floor"))
		color = color_get_pixel(ray->txt_floor->addr, txt_addr_idx);
	if (ray->wall == 1)
		color_shift_y(&color);
	env_addr_idx = I(4 * (WIDTH_1_4 * xy.y + get_thr_x(thr_id, xy.x)));
	color_set_pixel(ray->env->addr, env_addr_idx, color);
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
		draw_texture(ray, thr_id, xy, "wall");
		xy.y++;
	}
	while (xy.y < HEIGHT)
	{
		//draw_pixel(ray, thr_id, xy, COLOR_FLOOR);
		draw_texture(ray, thr_id, xy, "floor");

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
