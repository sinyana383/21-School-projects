/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:40:18 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 19:15:53 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h" 

int	quote_len(char *str)
{
	char	mark;
	int		i;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr(QUOT_MARKS, str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == '\\')
			return (just_print_error("syntax error", "\\", \
			"not required by the subject"));
		if (str[i] == mark)
			break ;
		i++;
	}
	if (str[i] != mark)
		return (just_print_error("syntax error", NULL, "no closing quote"));
	return (i + 1);
}

int	other_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (1);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (1);
	else if (*chr == 92 || *chr == ';' || *chr == '\\')
		return (1);
	else if (*chr == '|')
		return (1);
	return (0);
}

int	text_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(CLEARSPACES, str[i]))
			break ;
		else if (other_len(&str[i]) > 0)
			break ;
		else if (ft_strchr(QUOT_MARKS, str[i]))
			break ;
		i++;
	}
	return (i);
}

int	free_quote(char *token_str)
{
	free(token_str);
	return (just_print_error(NULL, NULL, strerror(ENOMEM)));
}
