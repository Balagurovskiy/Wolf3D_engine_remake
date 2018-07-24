/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:19:11 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img		*image_new(void *mlx, int w, int h, char *img_file)
{
	t_img	*img;

	img = NULL;
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
	{
		image_destroy(mlx, img);
		exit(1);
	}
	if (img_file == NULL)
		img->newi = mlx_new_image(mlx, w, h);
	else
		img->newi = mlx_xpm_file_to_image(mlx, img_file, &w, &h);
	img->addr = mlx_get_data_addr(img->newi, &img->bpp,
						&img->sizel, &img->endi);
	return (img);
}

void		image_destroy(void *mlx, t_img *img)
{
	if (img != NULL)
	{
		if (img->newi != NULL)
			mlx_destroy_image(mlx, img->newi);
		ft_memdel((void **)&img);
	}
}
