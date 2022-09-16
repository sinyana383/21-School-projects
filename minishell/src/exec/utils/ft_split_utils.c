/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:09:12 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:09:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	quotes_case(char const *s, int *i, int *len)
{
	char	quotes;

	quotes = s[*i];
	++(*i);
	while (s[*i] != quotes && s[*i])
		++(*i);
	*i += (s[*i] == quotes);
	++(*len);
}

static int	strs_count(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			quotes_case(s, &i, &len);
		else if (s[i] != c)
		{
			while (s[i] != c && s[i])
				++i;
			++len;
		}
		else
			++i;
	}
	return (len);
}

char	**alloc_strs(char const *s, char c, int *size)
{
	char	**strs;

	if (!s)
		return (0);
	*size = strs_count(s, c);
	strs = (char **)malloc(sizeof(char *) * (*size + 1));
	if (!strs)
		return (0);
	strs[*size] = 0;
	return (strs);
}
