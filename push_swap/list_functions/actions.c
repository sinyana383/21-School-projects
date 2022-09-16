/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:10:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 17:11:19 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

t_list	*find_node(t_list *list, int data)
{
	if (!list)
		return (0);
	while (list != 0)
	{
		if (list->data == data)
			return (list);
		list = list->next;
	}
	return (0);
}

int	ft_reach_lstsize(t_list *lst, int size)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
		if (i > size)
			return (i);
	}
	return (i);
}

void	push(t_list **a, t_list **b, char a_or_b)
{
	t_list	*first_a;

	first_a = *a;
	*a = (*a)->next;
	first_a->next = (*b);
	*b = first_a;
	write(1, "p", 1);
	write(1, &a_or_b, 1);
	write(1, "\n", 1);
}

void	swap(t_list **list, char a_or_b)
{
	t_list	*first;

	if (ft_reach_lstsize(*list, 2) < 2)
		return ;
	first = *list;
	*list = (*list)->next;
	first->next = (*list)->next;
	(*list)->next = first;
	write(1, "s", 1);
	write(1, &a_or_b, 1);
	write(1, "\n", 1);
}
