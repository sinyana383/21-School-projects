/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:09:30 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/17 12:11:11 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*dst_char;
	const char		*src_char;
	unsigned long	i;

	i = 0;
	dst_char = dst;
	src_char = src;
	if (!dst && !src)
		return (dst);
	if (dst > src)
	{
		while (len--)
			dst_char[len] = src_char[len];
	}
	else
	{
		while (i < len)
		{
			dst_char[i] = src_char[i];
			++i;
		}
	}
	return (dst);
}
