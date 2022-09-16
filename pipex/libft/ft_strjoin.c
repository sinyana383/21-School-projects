/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:00:54 by ddurrand          #+#    #+#             */
/*   Updated: 2022/02/13 13:24:43 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
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
	len = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)malloc(len + 2);
	if (!concat)
		return (0);
	fill_concat(concat, s1, s2);
	return (concat);
}
