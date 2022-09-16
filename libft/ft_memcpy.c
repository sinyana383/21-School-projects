/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:18:42 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/19 15:47:14 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long	i;
	char			*dest;
	const char		*sourc;

	i = 0;
	dest = dst;
	sourc = src;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		dest[i] = sourc[i];
		++i;
	}
	return (dst);
}
