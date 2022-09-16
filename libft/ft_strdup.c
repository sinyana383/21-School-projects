/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:25:21 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/20 10:59:47 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = (char *)malloc(len + 1);
	if (!s2)
	{
		return (0);
	}
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		++i;
	}
	s2[i] = '\0';
	return (s2);
}
