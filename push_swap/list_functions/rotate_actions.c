/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:02:29 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 13:11:59 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

static t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	rotate(t_list **list, char a)
{
	t_list	*first;

	first = *list;
	*list = first->next;
	first->next = 0;
	ft_lstlast(*list)->next = first;
	if (a != 0)
	{
		write(1, "r", 1);
		write(1, &a, 1);
		write(1, "\n", 1);
	}
}

void	rev_rotate(t_list **list, char a)
{
	t_list	*last;
	t_list	*temp;

	temp = *list;
	while (temp->next->next != 0)
		temp = temp->next;
	last = temp->next;
	temp->next = 0;
	last->next = *list;
	*list = last;
	if (a != 0)
	{
		write(1, "rr", 2);
		write(1, &a, 1);
		write(1, "\n", 1);
	}
}

void	rr(t_list **a_list, t_list **b_list)
{
	rotate(a_list, 0);
	rotate(b_list, 0);
	write(1, "rr\n", 3);
}

void	rrr(t_list **a_list, t_list **b_list)
{
	rev_rotate(a_list, 0);
	rev_rotate(b_list, 0);
	write(1, "rrr\n", 4);
}
