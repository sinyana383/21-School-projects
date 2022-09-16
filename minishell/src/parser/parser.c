/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:37:06 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 17:37:33 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_cmd	*parser(t_list **l_token)
{
	t_cmd	*l_cmd;
	t_cmd	*cmd;
	t_list	*next;

	l_cmd = NULL;
	while (*l_token != NULL)
	{
		cmd = cmd_create(cmd_type_token(*l_token));
		if (cmd == NULL || (cmd->type == CMD
				&& cmd_token_set(cmd, l_token) == ERROR))
		{
			if (cmd)
				ft_lstclear_cmd(&cmd, cmd_destroy);
			ft_lstclear_cmd(&l_cmd, cmd_destroy);
			return (NULL);
		}
		if (cmd->type != CMD)
		{
			next = (*l_token)->next;
			ft_lstdelone(*l_token, c_token_destroy);
			*l_token = next;
		}
		ft_lstadd_back_cmd(&l_cmd, cmd);
	}
	return (l_cmd);
}
