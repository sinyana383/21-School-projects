/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:07:29 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:11:36 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_strjoin_val(char *dst, const char *src, int len_src)
{
	int		i;
	int		j;
	int		len;
	char	*concat;

	if (!dst || !src)
		return (dst);
	len = ft_strlen(dst) + len_src;
	concat = (char *)malloc(len + 1);
	if (!concat)
	{
		free(dst);
		return (NULL);
	}
	i = -1;
	while (dst[++i])
		concat[i] = dst[i];
	free(dst);
	j = -1;
	while (src[++j] && j < len_src)
		concat[i + j] = src[j];
	concat[i + j] = '\0';
	return (concat);
}
