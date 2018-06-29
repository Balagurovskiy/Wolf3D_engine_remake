/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:08:33 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/08 18:47:22 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_clear(t_list *node)
{
	if (node && node->content)
	{
		free(node->content);
		node->content = NULL;
		node->content_size = 0;
	}
}
