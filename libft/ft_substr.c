/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:46:58 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/18 18:15:15 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*empty_alloc(void)
{
	char	*sub;

	sub = (char *)malloc(1);
	if (!sub)
		return (0);
	sub[0] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned long	i;
	unsigned long	j;
	char			*sub;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (empty_alloc());
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (0);
	i = start;
	j = 0;
	while (i < len + start && s[i])
	{
		sub[j] = s[i];
		++j;
		++i;
	}
	sub[j] = '\0';
	return (sub);
}
