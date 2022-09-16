/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:24:32 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/19 14:57:11 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\f')
		return (1);
	if (c == '\r' || c == ' ' || c == '\v')
		return (1);
	return (0);
}

static int	check_over(unsigned long long int res, int minus)
{
	if (res > 9223372036854775807)
	{
		if (minus == -1)
			return (0);
		return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						minus;
	unsigned long long int	res;

	i = 0;
	res = 0;
	minus = 1;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		++i;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		++i;
		if (check_over(res, minus) != 1)
			return (check_over(res, minus));
	}
	return ((long long int)res * minus);
}
