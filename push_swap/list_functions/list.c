/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:10:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 17:09:04 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

int	maxim(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	minim(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	check_a_list(t_list	**a_list, int *a)
{
	if (is_list_sorted(*a_list))
	{
		final_sort_list(a_list, find_node(*a_list, a[0])->data);
		ft_lstclear(a_list);
		return (1);
	}
	else if (ft_reach_lstsize(*a_list, 3) == 3)
	{
		sort_three(a_list);
		final_sort_list(a_list, a[0]);
		ft_lstclear(a_list);
		return (1);
	}
	return (0);
}

int	work_with_list(int *a, int len)
{
	t_list	*a_list;
	t_list	*b_list;

	a_list = make_list(a, len);
	if (a_list == 0)
		return (-1);
	sort(a, len - 1, 0);
	if (check_a_list(&a_list, a))
		return (1);
	b_list = make_b(&a_list, a, len);
	sort_three(&a_list);
	sort_b_to_a(&a_list, &b_list);
	final_sort_list(&a_list, a[0]);
	ft_lstclear(&a_list);
	return (1);
}
