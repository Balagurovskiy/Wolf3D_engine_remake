/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:49:08 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/08 18:47:35 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_add(t_list **first_node, t_list *new_node)
{
	t_list *f;

	if (*first_node != NULL)
	{
		f = *first_node;
		while (f)
		{
			if (f->next == NULL)
			{
				f->next = new_node;
				break ;
			}
			f = f->next;
		}
	}
	else
		*first_node = new_node;
}
