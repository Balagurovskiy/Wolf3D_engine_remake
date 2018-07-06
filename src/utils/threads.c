/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

	// while (0.01 < fabs((WIDTH_1_4 * idx) - x))

static void	display_0_1(t_win *win)
{
	display(win, 0, WIDTH_1_4);
}

static void	display_1_2(t_win *win)
{
	display(win, WIDTH_1_4, WIDTH_1_4 * 2);
}

static void	display_2_3(t_win *win)
{
	display(win, WIDTH_1_4 * 2, WIDTH_1_4 * 3);
}

static void	display_3_4(t_win *win)
{
	display(win, WIDTH_1_4 * 3, WIDTH_1_4 * 4);
}

void	thread_make(t_win *win)
{
	pthread_t		threads[4];
	int				idx;

	pthread_create(&threads[0], NULL,
			(void *(*)(void *))display_0_1,	(void *)win);
	// pthread_create(&threads[1], NULL,
	// 		(void *(*)(void *))display_1_2,	(void *)win);
	pthread_create(&threads[1], NULL,
			(void *(*)(void *))display_2_3,	(void *)win);
	// pthread_create(&threads[3], NULL,
	// 		(void *(*)(void *))display_3_4,	(void *)win);
	// idx = 0;
	// while (idx < 4)
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
}