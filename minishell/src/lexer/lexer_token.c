/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:55:20 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 19:09:21 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h" 

int	pipe_token(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '|')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_PIPE);
		if (token == NULL)
		{
			free(token_str);
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
		if (str[*i] == '|')
			return (just_print_error("syntax error", NULL, \
			"no command after pipe"));
	}
	return (0);
}

int	special_token(char *str, int *i)
{
	if (str[*i] == '(' || str[*i] == ')' || str[*i] == ';' || str[*i] == '\\')
		return (just_print_error("syntax error", NULL, \
		"(), ; or \\ are not required by the subject"));
	return (0);
}

int	redir_token(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = 0;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_REDIR);
		if (token == NULL)
		{
			free(token_str);
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += len;
	}
	return (0);
}

int	text_token(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = text_len(&str[*i]);
	if (len > 0)
	{
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_TEXT);
		if (token == NULL)
		{
			free(token_str);
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(CLEARSPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

int	quote_token(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = quote_len(&str[*i]);
	if (len == ERROR)
		return (ERROR);
	if (len > 0)
	{
		token_str = ft_substr(str, *i + 1, len - 2);
		if (token_str == NULL)
			return (just_print_error(NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '\'')
			token = token_create(token_str, TOK_TEXT | TOK_S_QUOTE);
		else
			token = token_create(token_str, TOK_TEXT | TOK_D_QUOTE);
		if (token == NULL)
			return (free_quote(token_str));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(CLEARSPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}
