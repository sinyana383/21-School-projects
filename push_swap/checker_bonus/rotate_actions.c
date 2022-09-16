/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:02:29 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/19 19:53:51 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	rotate(t_list **list)
{
	t_list	*first;

	if (ft_lstlast(*list) == *list)
		return ;
	first = *list;
	*list = first->next;
	first->next = 0;
	ft_lstlast(*list)->next = first;
}

void	rev_rotate(t_list **list)
{
	t_list	*last;
	t_list	*temp;

	if (ft_lstlast(*list) == *list)
		return ;
	temp = *list;
	while (temp->next->next != 0)
		temp = temp->next;
	last = temp->next;
	temp->next = 0;
	last->next = *list;
	*list = last;
}

void	rr(t_list **a_list, t_list **b_list)
{
	rotate(a_list);
	rotate(b_list);
}

void	rrr(t_list **a_list, t_list **b_list)
{
	rev_rotate(a_list);
	rev_rotate(b_list);
}
