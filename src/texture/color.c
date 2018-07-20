/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_color		color_get_pixel(char *addr, int idx)
{
	t_color color;

	color.r = addr[idx];
	color.g = addr[idx + 1];
	color.b = addr[idx + 2];

	return (color);
}

void		color_shift_y(t_color *color)
{
	color->r = (color->r >> 1) & 8355711;
	color->g = (color->g >> 1) & 8355711;
	color->b = (color->b >> 1) & 8355711;
}

void		color_set_pixel(char *addr, int idx, t_color color)
{
	addr[idx] = color.r;
	addr[idx + 1] = color.g;
	addr[idx + 2] = color.b;
}