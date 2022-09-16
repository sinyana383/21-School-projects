/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollars_open.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:08:20 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:24:20 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	initial_and_check(t_c_token *token, int *j, char **new_str)
{
	if (!token || !token->str || token->flags & TOK_S_QUOTE || \
	!ft_strchr(token->str, '$'))
		return (0);
	*j = 0;
	*new_str = ft_strdup("");
	if (!*new_str)
		return (print_errno_error("malloc", NULL));
	return (1);
}

int	get_and_concat_val(t_c_token *token, int *i, char **new_str)
{
	char	*val;

	val = 0;
	if (open_env_val(&val, token->str + *i, i) < 0)
	{
		free(*new_str);
		return (-1);
	}
	if (val)
	{
		*new_str = ft_strjoin_val(*new_str, val, ft_strlen(val));
		free(val);
		if (!*new_str)
			return (-1);
	}
	return (1);
}

int	last_addition(char **new_str, t_c_token *token, int j, int i)
{
	*new_str = ft_strjoin_val(*new_str, token->str + j, i - j);
	if (!*new_str)
		return (-1);
	free(token->str);
	token->str = *new_str;
	return (1);
}

int	open_token(t_c_token *token)
{
	char	*new_str;
	int		i;
	int		j;

	i = initial_and_check(token, &j, &new_str);
	if (i < 1)
		return (i);
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && token->str[i + 1] != '?')
		{
			new_str = ft_strjoin_val(new_str, token->str + j, i - j);
			if (!new_str)
				return (print_errno_error("malloc", NULL));
			else if (get_and_concat_val(token, &i, &new_str) < 0)
				return (-1);
			j = i;
			continue ;
		}
		++i;
	}
	return (last_addition(&new_str, token, j, i));
}

int	open_all_dollars(t_cmd *cmds)
{
	t_list	*temp;

	while (cmds)
	{
		if (cmds->type == CMD)
		{
			temp = cmds->argvs;
			while (temp)
			{
				open_token((t_c_token *)(temp->content));
				temp = temp->next;
			}
			temp = cmds->redirs;
			while (temp)
			{
				open_token((t_c_token *)(temp->content));
				temp = temp->next;
			}
		}
		cmds = cmds->next;
	}
	return (1);
}
