/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:44:11 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 16:53:11 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	fill_array(char **argv, int **a, int argc)
{
	int	ia;
	int	i;
	int	check;
	int	not_sorted;

	ia = 0;
	i = -1;
	not_sorted = 0;
	while (++i < argc)
	{
		check = ft_atoi(argv[i], *a, ia++);
		if (check < 0)
			return (-1);
		if (check == 0)
			not_sorted = 1;
	}
	if (!not_sorted)
		ia = 0;
	return (ia);
}

int	check_arg_and_a(int argc, char **argv, int **a)
{
	if (argc <= 1)
		return (0);
	*a = (int *)malloc(sizeof(int) * argc - 1);
	if (!(*a))
		return (-1);
	if (argc == 2)
	{
		if (ft_atoi(argv[1], *a, 0) < 0)
			return (-1);
		return (0);
	}
	return (fill_array(++argv, a, argc - 1));
}

int	main(int argc, char **argv)
{
	int	*a;
	int	size;

	a = 0;
	size = check_arg_and_a(argc, argv, &a);
	if (size < 1)
	{
		if (a != 0)
			free(a);
		if (size < 0)
			write(2, "Error\n", 6);
		return (0);
	}
	if (work_with_list(a, size) < 0)
		write(2, "Error\n", 6);
	free(a);
}
