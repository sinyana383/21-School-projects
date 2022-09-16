/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:42:47 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/20 10:54:37 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	res;
	unsigned long	dst_res_size;

	j = 0;
	dst_res_size = ft_strlen(dst);
	if (dst_res_size > dstsize)
		dst_res_size = dstsize;
	res = dst_res_size + ft_strlen(src);
	if (dstsize != 0)
	{
		i = ft_strlen(dst);
		while (i + j < dstsize - 1 && i + j < res)
		{
			dst[i + j] = src[j];
			++j;
		}
		if (dstsize > i)
			dst[i + j] = '\0';
	}
	return (res);
}
