/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:28:46 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:09:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	del_token(t_c_token	*token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	token->str = 0;
	free(token);
}

void	m_lstdelone(t_list *lst, void (*del)(t_c_token*))
{
	if (!lst)
		return ;
	del(lst->content);
	lst->next = NULL;
	free(lst);
}

int	lst_remove_next(t_list	*list)
{
	t_list	*remove;

	if (!list || !list->next)
		return (0);
	remove = list->next;
	list->next = remove->next;
	m_lstdelone(remove, del_token);
	return (1);
}
