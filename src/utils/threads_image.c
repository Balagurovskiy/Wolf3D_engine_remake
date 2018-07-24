/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	threads_set_image(t_win *win)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		win->ray[i]->env = image_new(win->mlx, WIDTH_1_4, HEIGHT, NULL);
		win->ray[i]->txt_floor = win->txts[4];
		win->ray[i]->txt = NULL;
		i++;
	}
}

void	threads_put_image(t_win *win)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		mlx_put_image_to_window(win->mlx, win->win,
								win->ray[i]->env->newi, (WIDTH_1_4 * i), 0);
		i++;
	}
}

void	threads_reset_image(t_win *win)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		mlx_destroy_image(win->mlx, win->ray[i]->env->newi);
		win->ray[i]->env->newi = mlx_new_image(win->mlx, WIDTH_1_4, HEIGHT);
		i++;
	}
}

void	threads_free_image(t_win *win)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		if (win->ray[i]->env != NULL)
			image_destroy(win->mlx, win->ray[i]->env);
		i++;
	}
}
