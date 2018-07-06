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

static void	draw_pixel(t_win *win, int x, int y, int color)
{
	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;	
	*(int *)(win->env->addr + (y * win->env->sizel) + (x * (win->env->bpp / 8))) = color;
}

void	draw(t_win *win, int x)
{
	int	y;

	y = 0;
	while (y < win->ray->l_start)
		draw_pixel(win, x, y++, 0xC00000A0);
	while (y >= win->ray->l_start && y <= win->ray->l_end)
		draw_pixel(win, x, y++, win->env->color);
	while (y < HEIGHT)
		draw_pixel(win, x, y++, 0xC00000A0);//COLOR_FLOOR
}
void test(t_win *win);
void		display(t_win *win, int x0, int xn)
{
	int		x;

	x = x0;
	while (x < xn)
	{
		raycast(win, x);
		
		if (win->ray->wall == 0)
			win->env->color = (win->ray->step.x < 0 ? COLOR_NORTH : COLOR_SOUTH);
		else
			win->env->color = (win->ray->step.y > 0 ? COLOR_EAST : COLOR_WEST);

		draw(win, x);
		x++;
	}
	test(win);
}

void test(t_win *win)
{

	// static int entry = 0;
	// 	if (entry == 11)
	// {
		printf("pos dx:%f dy:%f x:%d y:%d\n", win->ray->pos.dx,win->ray->pos.dy,win->ray->pos.x,win->ray->pos.y);
		printf("Rdir dx:%f dy%f\n", win->ray->dir.dx, win->ray->dir.dy);
		printf("plane dx:%f dy%f\n", win->ray->plane.dx, win->ray->plane.dy);
		printf("dir dx:%f dy%f\n ", win->dir.dx, win->dir.dy);
		printf("delta dx:%f dy%f\n", win->ray->delta.dx, win->ray->delta.dy);
		printf("step dx:%d dy%d\n", win->ray->step.x,win->ray->step.y);
		printf("dist dx:%f dy%f\n", win->ray->dist.dx,win->ray->dist.dy);
		printf("start end dx:%d dy:%d rh:%d\n\n", win->ray->l_start,win->ray->l_end,win->ray->l_h);
	// }
	// entry++;
	// if (entry == 1000)
	// 	entry = 0;
}
