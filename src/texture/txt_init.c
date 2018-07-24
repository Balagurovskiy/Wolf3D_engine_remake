/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img		**txt_init(void *mlx)
{
	t_img		**txt;

	txt = (t_img **)malloc(sizeof(t_img *) * TXTS);
	if (!txt)
		return (NULL);
	txt[0] = image_new(mlx, WIDTH_1_4, HEIGHT, "textures/1j.xpm");
	txt[1] = image_new(mlx, WIDTH_1_4, HEIGHT, "textures/12j.xpm");
	txt[2] = image_new(mlx, WIDTH_1_4, HEIGHT, "textures/13j.xpm");
	txt[3] = image_new(mlx, WIDTH_1_4, HEIGHT, "textures/14j.xpm");
	txt[4] = image_new(mlx, WIDTH_1_4, HEIGHT, "textures/0j.xpm");
	return (txt);
}

void		txt_free(void *mlx, t_img **txts)
{
	int i;

	i = 0;
	if (txts != NULL)
	{
		while (i < TXTS)
		{
			if (txts[i] != NULL)
				image_destroy(mlx, txts[i]);
			i++;
		}
		ft_memdel((void **)&(txts));
	}
}
