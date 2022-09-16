/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:02:49 by ddurrand          #+#    #+#             */
/*   Updated: 2022/02/13 15:04:57 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

static char	*allo_cpy(const char *p, char c, int *j)
{
	int		i;
	char	*s;

	i = 0;
	while (p[i] != c && p[i])
		++i;
	s = (char *)malloc(i + 1);
	if (!s)
		return (0);
	i = 0;
	while (p[i] != c && p[i])
	{
		s[i] = p[i];
		++i;
	}
	*j += i;
	s[i] = '\0';
	return (s);
}

static void	free_prev(char **strs, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}

void	fill_strs_elem(char	**elem, char const *s, int *j, char c)
{
	char	quotes;

	if (s[*j] == '\'' || s[*j] == '\"')
	{
		quotes = s[*j];
		*elem = allo_cpy((s + ++(*j)), quotes, j);
		*j += (s[*j] == quotes);
	}
	else
		*elem = allo_cpy((s + *j), c, j);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		size;

	strs = alloc_strs(s, c, &size);
	if (!strs)
		return (0);
	i = -1;
	j = 0;
	while (++i < size)
	{
		while (s[j] == c)
				++j;
		if (*(s + j))
		{
			fill_strs_elem(&(strs[i]), s, &j, c);
			if (!(strs[i]))
			{
				free_prev(strs, i);
				return (0);
			}
		}
	}
	return (strs);
}
