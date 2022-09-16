/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:25:30 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 18:25:18 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_list	*get_list_token(char *input)
{
	t_list	*l_token;
	int		i;

	l_token = NULL;
	i = 0;
	while (input && input[i])
	{
		if (pipe_token(input, &i, &l_token) == ERROR)
			break ;
		if (special_token(input, &i) == ERROR)
			break ;
		if (redir_token(input, &i, &l_token) == ERROR)
			break ;
		if (text_token(input, &i, &l_token) == ERROR)
			break ;
		if (quote_token(input, &i, &l_token) == ERROR)
			break ;
		while (input[i] && ft_strchr(CLEARSPACES, input[i]))
			i++;
	}
	if (input[i] != '\0')
		ft_lstclear(&l_token, c_token_destroy);
	return (l_token);
}

int	syntax_pipe(t_list *l_token)
{
	if (l_token && token_content(l_token)->flags & TOK_PIPE)
		return (just_print_error("syntax error near unexpected token", \
		NULL, "\'|\'"));
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_PIPE)
		{
			if (l_token->next == NULL || \
			(token_content(l_token->next)->flags & TOK_PIPE))
				return (just_print_error("syntax error", NULL, \
				"no command after pipe"));
		}
		l_token = l_token->next;
	}
	return (0);
}

int	redir_files(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_REDIR)
		{
			if (l_token->next == NULL
				|| !(token_content(l_token->next)->flags & TOK_TEXT))
				return (just_print_error("syntax error", NULL, \
				"no file or limiter after redirect"));
			l_token = l_token->next;
			token_content(l_token)->flags |= TOK_REDIR_FILE;
			while (token_content(l_token)->flags & TOK_CONNECTED)
			{
				token_content(l_token->next)->flags |= TOK_REDIR_FILE;
				l_token = l_token->next;
			}
		}
		l_token = l_token->next;
	}
	return (0);
}

t_list	*lexer(char *str)
{
	t_list		*l_token;

	l_token = get_list_token(str);
	if (l_token == NULL)
		return (NULL);
	if (syntax_pipe(l_token) == ERROR)
	{
		set_status(258);
		ft_lstclear(&l_token, c_token_destroy);
		return (NULL);
	}
	if (redir_files(l_token) == ERROR)
	{
		set_status(258);
		ft_lstclear(&l_token, c_token_destroy);
		return (NULL);
	}
	return (l_token);
}
