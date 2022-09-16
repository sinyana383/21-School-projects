/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:02:36 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/20 13:02:40 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int argc, char **argv)
{
	int	*a;
	int	size;

	a = 0;
	size = check_arg_and_a(argc, argv, &a);
	if (size < 0)
	{
		if (a != 0)
			free(a);
		if (size == -1)
			write(2, "Error\n", 6);
		exit (-1);
	}
	if (list(a, size) < 0)
		write(2, "Error\n", 6);
	free(a);
	exit (1);
}
