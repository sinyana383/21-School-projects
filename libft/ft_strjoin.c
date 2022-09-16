/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:21:49 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/13 17:34:20 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*concat;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)malloc(len + 1);
	if (!concat)
		return (0);
	i = 0;
	while (s1[i])
	{
		concat[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		concat[i + j] = s2[j];
		++j;
	}
	concat[i + j] = '\0';
	return (concat);
}
