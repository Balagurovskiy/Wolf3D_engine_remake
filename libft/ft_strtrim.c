/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 17:41:09 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 12:15:00 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_space(char c)
{
	if (c == ' ' || c == '\n' ||
		c == '\t' || c == '\v' ||
		c == '\f' || c == '\r')
		return (1);
	return (0);
}

static	void	get_limits(int *start, int *end, char const *s)
{
	int i;
	int flag;

	i = 0;
	flag = 1;
	while (s[i])
	{
		if (!is_space(s[i]) && flag)
		{
			*start = i;
			flag = 0;
		}
		i++;
	}
	flag = 1;
	while (i)
	{
		if (!is_space(s[i]) && flag && s[i] != '\0')
		{
			(*end) = i;
			flag = 0;
		}
		i--;
	}
}

char			*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	char	*res;
	int		i;

	if (s)
	{
		i = 0;
		start = 0;
		end = 0;
		get_limits(&start, &end, s);
		res = (char *)malloc(sizeof(char) * (end - start + 1) + 1);
		if (res == NULL)
			return (NULL);
		while ((start <= end) && (ft_strlen(s)))
		{
			res[i] = s[start];
			start++;
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (0);
}
