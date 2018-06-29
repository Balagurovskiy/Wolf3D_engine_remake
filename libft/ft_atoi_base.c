/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <arudenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 10:08:03 by arudenko          #+#    #+#             */
/*   Updated: 2018/01/15 11:01:23 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' ||
		c == '\t' || c == '\v' ||
		c == '\f' || c == '\r')
		return (1);
	return (0);
}

static	int	get_base_id(char c, int base)
{
	char	*digits;
	int		i;

	digits = "0123456789abcdef";
	i = 0;
	while (i < base)
	{
		if (digits[i] == ft_tolower(c))
			return (i);
		i++;
	}
	return (-1);
}

int			ft_atoi_base(const char *str, int base)
{
	int			minus;
	long long	res;

	minus = 0;
	res = 0;
	while (is_space(*str))
		str++;
	if (*str == '-')
		minus = 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		res = (res * base) + get_base_id(*str, base);
		str++;
	}
	return ((minus) ? -res : res);
}
