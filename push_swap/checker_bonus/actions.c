/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:10:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/20 12:56:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

void	push(t_list **a, t_list **b)
{
	t_list	*first_a;

	if (ft_reach_lstsize(*a, 2) < 1)
		return ;
	first_a = *a;
	*a = (*a)->next;
	first_a->next = (*b);
	*b = first_a;
}

void	swap(t_list **list)
{
	t_list	*first;

	if (ft_reach_lstsize(*list, 2) < 2)
		return ;
	first = *list;
	*list = (*list)->next;
	first->next = (*list)->next;
	(*list)->next = first;
}

void	ss(t_list **a, t_list **b)
{
	swap(a);
	swap(b);
}
