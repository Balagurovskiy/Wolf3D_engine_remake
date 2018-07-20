/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 12:57:43 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 11:53:51 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*rez;

	if (s)
	{
		i = 0;
		rez = (char *)malloc(sizeof(char) * len + 1);
		if (rez == NULL)
			return (NULL);
		s += start;
		while (i < len)
		{
			rez[i] = *s;
			i++;
			s++;
		}
		rez[i] = '\0';
		return (rez);
	}
	return (0);
}
