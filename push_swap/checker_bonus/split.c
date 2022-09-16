/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:39:51 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/19 17:57:52 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	strs_count(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
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

static char	**alloc_strs(char const *s, char c, int *size)
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
			strs[i] = allo_cpy((s + j), c, &j);
			if (!(strs[i]))
			{
				free_prev(strs, i);
				return (0);
			}
		}
	}
	return (strs);
}
