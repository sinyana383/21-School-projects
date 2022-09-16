/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:13:19 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/18 17:20:59 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

int	is_min_max_mid(int data, int *a, int len)
{
	if (data == a[0] || data == a[len / 2] || data == a[len - 1])
		return (1);
	return (0);
}

void	act_with_min_max_mid(t_list **a_list, int *a, int len)
{
	if (is_min_max_mid((*a_list)->next->data, a, len) \
		&& is_min_max_mid((*a_list)->next->next->data, a, len) \
		&& ft_reach_lstsize((*a_list)->next->next->next, 3) < 3 && len == 5)
		rev_rotate(a_list, 'a');
	else
		rotate(a_list, 'a');
}

t_list	*make_b(t_list **a_list, int *a, int len)
{
	t_list	*b_list;
	t_list	*temp;
	int		i;
	int		flag;

	temp = 0;
	i = 1;
	b_list = 0;
	flag = -1;
	while (ft_reach_lstsize(*a_list, 3) > 3)
	{
		if ((*a_list)->data == a[len / 2])
			flag += 1;
		if (is_min_max_mid((*a_list)->data, a, len))
			act_with_min_max_mid(a_list, a, len);
		else if ((*a_list)->data < a[len / 2] || (flag >= 1) || len < 200)
			push(a_list, &b_list, 'b');
		else
			rotate(a_list, 'a');
	}
	return (b_list);
}
