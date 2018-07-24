/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		txt_draw_wall(t_ray *ray, int thr_id, t_xy xy)
{
	int				d;
	t_color			color;
	int				txt_addr_idx;
	int				env_addr_idx;

	if (out_of_range(thr_id, xy))
		return ;
	d = xy.y * 2 - HEIGHT + ray->l_h;
	if (ray->l_h)
		ray->t_y = ((d * TXT_H / ray->l_h) / 2);
	else
		ray->t_y = (d * TXT_H / 2);
	txt_addr_idx = I(4 * (TXT_H * ray->t_y + ray->t_x));
	color = txt_color_get_addr(ray->txt->addr, txt_addr_idx);
	if (ray->wall == 1)
		txt_color_shift_y(&color);
	env_addr_idx = I(4 * (WIDTH_1_4 * xy.y + get_thr_x(thr_id, xy.x)));
	txt_color_set_pixel(ray->env->addr, env_addr_idx, color);
}

void		txt_draw_floor(t_ray *ray, int thr_id, t_xy xy, double dist)
{
	t_xy			curr_f;
	t_color			color;
	int				txt_addr_idx;
	int				env_addr_idx;

 	if (out_of_range(thr_id, xy))
		return ;
	curr_f.dy = HEIGHT / (2.0 * xy.y - HEIGHT);
	curr_f.dx = (curr_f.dy) / (dist);

	curr_f.x = I((curr_f.dx * ray->floor.dx + (1.0 - curr_f.dx) * ray->pos.dx) * TXT_W / 1) % TXT_W;
	curr_f.y = I((curr_f.dx * ray->floor.dy + (1.0 - curr_f.dx) * ray->pos.dy) * TXT_H / 1) % TXT_H;

	// curr_f.x = I((curr_f.dx * ray->floor.dx + (1.0 - curr_f.dx) * 11) * TXT_W / 1) % TXT_W;
	// curr_f.y = I((curr_f.dx * ray->floor.dy + (1.0 - curr_f.dx) * 11) * TXT_H / 1) % TXT_H;

	txt_addr_idx = I(4 * (TXT_H * curr_f.y + curr_f.x));
	color = txt_color_get_addr(ray->txt_floor->addr, txt_addr_idx);

	env_addr_idx = I(4 * (WIDTH_1_4 * xy.y + get_thr_x(thr_id, xy.x)));
	txt_color_set_pixel(ray->env->addr, env_addr_idx, color);
}
