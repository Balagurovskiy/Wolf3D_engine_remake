/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:01:15 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 12:00:24 by obalagur         ###   ########.fr       */
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

static int	is_number(char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

int			ft_atoi(const char *str)
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
	while (is_number(*str))
	{
		if ((res > 922337203685477580 || (res == 922337203685477580
		&& (*str - '0') > 7)) && minus == 0)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580
		&& (*str - '0') > 8)) && minus == 1)
			return (0);
		res = (res * 10) + *str - '0';
		str++;
	}
	return ((minus) ? -res : res);
}
