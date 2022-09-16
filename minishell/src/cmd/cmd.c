/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:40:38 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 17:40:49 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

int	cmd_type_token(t_list *token)
{
	if (token == NULL)
		return (ERROR);
	else if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (CMD);
	else if (token_content(token)->flags & TOK_PIPE)
		return (CMD_PIPE);
	return (ERROR);
}

t_cmd	*cmd_create(int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = type;
	cmd->argvs = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	if (cmd->argvs)
		ft_lstclear(&(cmd->argvs), c_token_destroy);
	if (cmd->redirs)
		ft_lstclear(&(cmd->redirs), c_token_destroy);
}

void	ft_lstdelone_cmd(t_cmd *lst, void (del)(t_cmd *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst);
		free(lst);
	}
}

void	ft_lstclear_cmd(t_cmd **lst, void (del)(t_cmd *))
{
	t_cmd	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lstdelone_cmd(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
