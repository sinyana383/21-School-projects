/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:57:33 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/17 19:18:33 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	unsigned int		len;
	char				*res;

	i = -1;
	if (!s)
		return (0);
	len = ft_strlen(s);
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);
	while (++i < len)
		res[i] = f(i, s[i]);
	res[i] = '\0';
	return (res);
}
