/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_and_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:39:51 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/20 11:57:19 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	fill_array(char **str, int **a, int argc)
{
	int	ia;
	int	i;
	int	check;

	ia = 0;
	i = -1;
	while (++i < argc)
	{
		check = ft_atoi(str[i], *a, ia++);
		if (check < 0)
			return (-1);
	}
	return (ia);
}

int	init_and_check(int *ia, int *i, char str)
{
	*ia = 0;
	*i = 0;
	if (!str)
		return (-1);
	return (1);
}

int	check_string_and_fill_array(char *str, int **a)
{
	int	i;
	int	j;
	int	check;
	int	ia;

	if (init_and_check(&ia, &i, *str) < 0)
		return (-1);
	while (str[i])
	{
		j = 0;
		while (str[i + j] != ' ' && str[i + j])
			++j;
		if (str[i + j] == ' ')
			str[i + j++] = '\0';
		check = ft_atoi(str + i, *a, ia++);
		if (check < 0)
			return (-1);
		i += j;
	}
	return (ia);
}

int	two_argc(int **a, char **argv)
{
	char	**str;
	int		i;
	int		res;

	if (!argv[1][0])
		return (-1);
	str = ft_split(*(argv + 1), ' ');
	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		;
	*a = (int *)malloc(sizeof(int) * i);
	if (!(*a))
		return (-1);
	res = fill_array(str, a, i);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (res);
}

int	check_arg_and_a(int argc, char **argv, int **a)
{
	if (argc <= 1)
		return (-2);
	if (argc == 2)
		return (two_argc(a, argv));
	*a = (int *)malloc(sizeof(int) * argc - 1);
	if (!(*a))
		return (-1);
	return (fill_array(++argv, a, argc - 1));
}
