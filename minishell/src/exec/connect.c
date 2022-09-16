/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:38:06 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 15:34:21 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_and_tokconn_and_tokrem(t_list **list, \
char *list_str, t_list *tmp_token)
{
	free(con_token(*list)->str);
	con_token(*list)->str = list_str;
	if (!(con_token(tmp_token)->flags & TOK_CONNECTED))
		con_token(*list)->flags &= ~TOK_CONNECTED;
	lst_remove_next(*list);
}

int	connecting(t_list *list)
{
	t_list	*tmp_token;
	char	*list_str;
	char	*tmp_token_str;

	if (!list || !list->next)
		return (1);
	while (list)
	{
		while ((con_token(list)->flags & TOK_CONNECTED \
		&& list->next))
		{
			list_str = ft_strdup(con_token(list)->str);
			if (!list_str)
				return (print_errno_error("malloc", NULL));
			tmp_token = list->next;
			tmp_token_str = con_token(tmp_token)->str;
			list_str = ft_strjoin_val(list_str, tmp_token_str, \
			ft_strlen(tmp_token_str));
			if (!list_str)
				return (print_errno_error("malloc", NULL));
			free_and_tokconn_and_tokrem(&list, list_str, tmp_token);
		}
		list = list->next;
	}
	return (1);
}

int	connect_all(t_cmd *cmd)
{
	if (connecting(cmd->argvs) < 0 || connecting(cmd->redirs) < 0)
		return (-1);
	return (1);
}
