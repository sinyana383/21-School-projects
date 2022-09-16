/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:29:58 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 17:31:04 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*token_create(char *string, int type)
{
	t_c_token	*c_token;
	t_list		*token;

	c_token = malloc(sizeof(t_c_token));
	if (c_token == NULL)
		return (NULL);
	c_token->flags = type;
	c_token->str = string;
	token = ft_lstnew(c_token);
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

void	c_token_destroy(void *c_token)
{
	free(((t_c_token *)c_token)->str);
	((t_c_token *)c_token)->str = NULL;
	free(c_token);
}

t_c_token	*token_content(t_list *token)
{
	return ((t_c_token *)token->content);
}

char	*token_to_str(t_list *token)
{
	char	*str;
	char	*tmp;

	if (token == NULL || token_content(token)->str == NULL)
		return (NULL);
	str = ft_strdup(token_content(token)->str);
	while (token && (token_content(token)->flags & TOK_CONNECTED))
	{
		tmp = str;
		str = ft_strjoin(str, token_content(token->next)->str);
		free(tmp);
		if (str == NULL)
			return (NULL);
		token = token->next;
	}
	return (str);
}
