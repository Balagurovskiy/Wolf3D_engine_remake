/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:06:41 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 12:09:22 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		join(char *rez, char const *s1, char const *s2)
{
	if (s1)
		while (*s1)
			*rez++ = *s1++;
	if (s2)
		while (*s2)
			*rez++ = *s2++;
	*rez = '\0';
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*rez;

	len = 0;
	if (!s1 && !s2)
		return (0);
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	rez = (char *)malloc(sizeof(char) * len + 1);
	if (rez == NULL)
		return (NULL);
	join(rez, s1, s2);
	return (rez);
}
