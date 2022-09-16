/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:27:12 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/20 13:38:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;
	t_list	**start_res;

	if (!lst)
		return (0);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (NULL);
	start_res = &res;
	tmp = res;
	while (lst->next)
	{
		lst = lst->next;
		tmp->next = ft_lstnew(f(lst->content));
		if (!(tmp->next))
		{
			ft_lstclear(start_res, del);
			return (0);
		}
		tmp = tmp->next;
	}
	return (*start_res);
}
