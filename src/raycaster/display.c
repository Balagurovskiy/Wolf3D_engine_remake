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
		draw_pixel(win, x, y++, COLOR_FLOOR);
}

void		display(t_win *win)
{
	static int		x;
	static	double	idx = 1;

	x = 0;
	// while (0.01 < fabs((WIDTH_1_4 * idx) - x))
	while (x<WIDTH)
	{
		raycast(win, x);
		
		if (win->ray->wall == 0)
			win->env->color = (win->ray->step.x < 0 ? COLOR_NORTH : COLOR_SOUTH);
		else
			win->env->color = (win->ray->step.y > 0 ? COLOR_EAST : COLOR_WEST);

		draw(win, x);
		x++;
	}
	idx++;
	if (idx > 4.0)
		idx = 1.0;
	if (x > WIDTH)
		x = 0;
}
