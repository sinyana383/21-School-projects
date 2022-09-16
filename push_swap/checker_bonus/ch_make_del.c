/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_make_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:10:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/19 16:58:59 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_list	*ft_lstnew(int data)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list));
	if (!new_lst)
		return (0);
	new_lst->data = data;
	new_lst->next = NULL;
	return (new_lst);
}

t_list	*make_list(int *a, int len)
{
	t_list	*list_a;
	t_list	*temp;
	int		i;

	i = 0;
	list_a = ft_lstnew(a[i]);
	if (!list_a)
		return (0);
	temp = list_a;
	while (++i < len)
	{
		temp = (temp->next = ft_lstnew(a[i]));
		if (!temp)
		{
			ft_lstclear(&list_a);
			return (0);
		}
	}
	return (list_a);
}

void	ft_lstclear(t_list **lst)
{
	if (!lst || !*lst)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next));
	free(*lst);
	*lst = NULL;
}
