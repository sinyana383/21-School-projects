/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:16:29 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/09 14:46:37 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	char			*b_char;

	i = 0;
	b_char = b;
	while (i < len)
	{
		b_char[i] = (unsigned char)c;
		++i;
	}
	return (b);
}
