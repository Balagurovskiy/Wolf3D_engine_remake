/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splinter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:49:24 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 11:49:40 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_it_c(char s, char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (s == c[i])
			return (1);
		i++;
	}
	return (0);
}

static char		**lower_mem(char const *s, char *c)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (!is_it_c(s[i], c))
		{
			while (!is_it_c(s[i], c) && (s[i] != '\0'))
				i++;
			len++;
		}
		if (s[i] != '\0')
			i++;
	}
	return ((char **)malloc(sizeof(char*) * len + 1));
}

static void		upper_mem(char const *s, char *c, char **res)
{
	size_t		i;
	size_t		len_temp;
	size_t		len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (!is_it_c(s[i], c))
		{
			len_temp = 0;
			while (!is_it_c(s[i], c) && (s[i] != '\0'))
			{
				i++;
				len_temp++;
			}
			res[len] = (char *)malloc(sizeof(char) * len_temp + 1);
			len++;
		}
		if (s[i] != '\0')
			i++;
	}
}

static void		filler(char const *s, char *c, char **res)
{
	size_t		i;
	size_t		len_temp;
	size_t		len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (!is_it_c(s[i], c))
		{
			len_temp = 0;
			while (!is_it_c(s[i], c) && (s[i] != '\0'))
			{
				res[len][len_temp] = s[i];
				i++;
				len_temp++;
			}
			res[len][len_temp] = '\0';
			len++;
		}
		if (s[i] != '\0')
			i++;
	}
	res[len] = 0;
}

char			**ft_splinter(char const *s, char *c)
{
	char	**res;

	if (s)
	{
		res = lower_mem(s, c);
		if (res == NULL)
			return (NULL);
		upper_mem(s, c, res);
		filler(s, c, res);
		return (res);
	}
	return (0);
}
