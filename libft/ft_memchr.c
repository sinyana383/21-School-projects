/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:57:23 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/19 15:43:35 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			c2;
	const unsigned char		*s2;
	unsigned long			i;

	i = 0;
	s2 = s;
	c2 = (unsigned char)c;
	if (n <= 0)
		return (0);
	while (s2[i] != c2 && i < n - 1)
		++i;
	if (s2[i] == c2)
		return ((void *)(s2 + i));
	return (0);
}
