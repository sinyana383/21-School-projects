/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:05:02 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/21 16:00:53 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char		*memory;
	size_t		i;

	memory = (char *)malloc(size * count);
	if (!memory)
	{
		return (0);
	}
	i = 0;
	while (i < count * size)
	{
		memory[i] = 0;
		++i;
	}
	return (memory);
}
