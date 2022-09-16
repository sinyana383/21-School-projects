/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:56:19 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/19 15:33:14 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;
	char			*s_char;

	if (n <= 0)
		return ;
	i = 0;
	s_char = s;
	while (i < n)
	{
		s_char[i] = 0;
		++i;
	}
}
