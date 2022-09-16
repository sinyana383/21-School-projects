/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:24:32 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 17:48:46 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

static int	check_over(unsigned	int res, int minus)
{
	if ((res > 2147483647 && minus > 0)
		|| res > 2147483648)
	{
		return (-1);
	}
	return (1);
}

void	plus_minus(const char *str, int *i, int *minus)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*minus = -1;
		++(*i);
	}
}

int	check_dub(int *a, int ia)
{
	int	i;

	i = -1;
	while (++i < ia)
	{
		if (a[i] == a[ia])
			return (-1);
	}
	return (1);
}

int	is_sorted(int *a, int ia)
{
	if (ia == 0)
		return (1);
	if (a[ia] > a[ia - 1])
		return (1);
	return (0);
}

int	ft_atoi(const char *str, int *a, int ia)
{
	int			i;
	int			minus;
	long int	res;

	i = 0;
	res = 0;
	minus = 1;
	plus_minus(str, &i, &minus);
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (-1);
		res *= 10;
		res += str[i] - '0';
		++i;
		if (check_over(res, minus) < 0)
			return (-1);
	}
	a[ia] = res * minus;
	if (check_dub(a, ia) < 0)
		return (-1);
	return (is_sorted(a, ia));
}
