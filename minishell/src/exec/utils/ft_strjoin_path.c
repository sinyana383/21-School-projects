/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:00:54 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:11:28 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	m_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		++i;
	return (i);
}

void	fill_concat(char *concat, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		concat[i] = s1[i];
		++i;
	}
	concat[i++] = '/';
	j = 0;
	while (s2[j])
	{
		concat[i + j] = s2[j];
		++j;
	}
	concat[i + j] = '\0';
}

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	int		len;
	char	*concat;

	if (!s1 || !s2)
		return (0);
	len = m_strlen(s1) + m_strlen(s2);
	concat = (char *)malloc(len + 2);
	if (!concat)
		return (0);
	fill_concat(concat, s1, s2);
	return (concat);
}
