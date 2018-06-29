/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:31:38 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 20:10:01 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_delete(t_list **delete, void (*del)(t_list *))
{
	del(*delete);
	free(*delete);
	*delete = NULL;
}

void			ft_lst_delone(t_list **f, t_list *one, void (*del)(t_list *))
{
	t_list	*loop;
	t_list	*delete;

	if (f && del)
	{
		loop = *f;
		if (loop == one)
		{
			*f = loop->next;
			ft_delete(&loop, del);
			return ;
		}
		while (loop)
		{
			if (loop->next == one)
			{
				delete = loop->next;
				loop->next = loop->next->next;
				ft_delete(&delete, del);
			}
			loop = loop->next;
		}
	}
}
