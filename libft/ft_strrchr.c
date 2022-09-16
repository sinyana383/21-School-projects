/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:04:48 by ddurrand          #+#    #+#             */
/*   Updated: 2021/10/20 10:11:37 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;
	char	c1;

	i = 0;
	res = 0;
	c1 = (char)c;
	while (s[i])
	{
		if (s[i] == c1)
			res = (char *)s + i;
		++i;
	}
	if (s[i] == c1)
		res = (char *)s + i;
	return (res);
}
