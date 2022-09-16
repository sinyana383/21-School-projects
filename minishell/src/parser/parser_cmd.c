/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:31:46 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 18:13:04 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	redir_type(char *redir)
{
	int	i;

	if (redir == NULL)
		return (ERROR);
	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		return (REDIR_OUT);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		return (REDIR_OUT_APP);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		return (REDIR_IN);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (ERROR);
}

int	cmd_token_set(t_cmd *cmd, t_list **l_token)
{
	t_list	*next;

	while (cmd_type_token(*l_token) == CMD)
	{
		next = (*l_token)->next;
		if (token_content(*l_token)->flags & TOK_REDIR)
		{
			if (redir_type(token_content(*l_token)->str) == REDIR_HEREDOC)
			{
				if (parser_heredoc(*l_token) == ERROR)
					return (ERROR);
			}
			ft_lstadd_back(&(cmd->redirs), *l_token);
		}
		else if (token_content(*l_token)->flags & TOK_REDIR_FILE)
			ft_lstadd_back(&(cmd->redirs), *l_token);
		else
			ft_lstadd_back(&(cmd->argvs), *l_token);
		(*l_token)->next = NULL;
		(*l_token) = next;
	}
	return (0);
}
