/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:04:26 by ddurrand          #+#    #+#             */
/*   Updated: 2022/05/31 13:09:52 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		++i;
	return (i);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

int	ft_putstr_error(char *s)
{
	if (!s)
		return (-2);
	write(1, s, ft_strlen(s));
	return (-1);
}

void	print_unsigned_number(unsigned long int num, int base, char x)
{
	char	c;

	if (num >= (unsigned long)base)
		print_unsigned_number(num / base, base, x);
	c = num % base;
	if (c > 9)
		c = c - 10 + x;
	else
		c = c + '0';
	write(1, &c, 1);
}
