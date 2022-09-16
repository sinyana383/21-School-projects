/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:44:02 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 11:55:55 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "../list_functions/list.h"

void static	right_left(int *a, int *right, int *left, int cur)
{
	while (*right > (*left))
	{
		while (a[*right] > cur && *right > (*left))
			--(*right);
		if (*right > (*left))
		{
			a[(*left)] = a[*right];
			++(*left);
		}
		while (a[(*left)] < cur && (*left) < *right)
			++(*left);
		if ((*left) < *right)
		{
			a[*right] = a[(*left)];
			--(*right);
		}
	}
}

void	sort(int *a, int right, int left)
{
	int	r_bord;
	int	l_bord;
	int	cur;

	r_bord = right;
	l_bord = left;
	cur = a[left];
	right_left(a, &right, &left, cur);
	a[left] = cur;
	cur = left;
	left = l_bord;
	right = r_bord;
	if (left < cur)
		sort(a, cur - 1, left);
	if (right > cur)
		sort(a, right, cur + 1);
}
