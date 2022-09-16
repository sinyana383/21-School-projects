/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:54:37 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/20 10:06:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	fill_str_trimmed(char *str, int end, int start, char const *s1)
{
	int	j;
	int	i;

	i = start;
	j = 0;
	while (i <= end)
	{
		str[j] = s1[i];
		++j;
		++i;
	}
	str[j] = '\0';
}

static int	find_end(char const *s1, char const *set, int i)
{
	int	end;

	while (s1[i])
	{
		if (!ft_strchr(set, s1[i]))
			end = i;
		++i;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*str_trimmed;

	if (s1 == 0 || set == 0)
		return (0);
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		++i;
	if (s1[i] == '\0')
	{
		str_trimmed = malloc(1);
		if (!str_trimmed)
			return (0);
		str_trimmed[0] = '\0';
		return (str_trimmed);
	}
	start = i;
	end = find_end(s1, set, i);
	str_trimmed = (char *)malloc((end - start + 1) + 1);
	if (!str_trimmed)
		return (0);
	fill_str_trimmed(str_trimmed, end, start, s1);
	return (str_trimmed);
}
