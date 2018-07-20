/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 13:27:40 by obalagur          #+#    #+#             */
/*   Updated: 2018/04/07 13:27:42 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			add_node(void **first_node, void *new_node)
{
	void *f;

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

void			del_node(void **alst)
{
	void *del_temp;

	if (*alst)
	{
		while (*alst)
		{
			del_temp = *alst;
			*alst = (*alst)->next;
			free(del_temp);
			del_temp = NULL;
		}
	}
}