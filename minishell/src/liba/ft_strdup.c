/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:38:20 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 17:38:21 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*s2;

	len_s1 = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (len_s1 + 1));
	if (s2 == NULL)
		return (NULL);
	s2 = (char *)ft_memcpy(s2, s1, len_s1 + 1);
	return (s2);
}
