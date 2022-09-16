/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:27:31 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/19 15:44:49 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	const char		*s1_char;
	const char		*s2_char;

	i = 0;
	s1_char = s1;
	s2_char = s2;
	if (n <= 0)
		return (0);
	while (s1_char[i] == s2_char[i] && i < n - 1)
		++i;
	return ((unsigned char)s1_char[i] - (unsigned char)s2_char[i]);
}
