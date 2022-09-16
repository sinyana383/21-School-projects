/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:11:47 by ddurrand          #+#    #+#             */
/*   Updated: 2021/11/15 15:48:02 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nl(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);
		++i;
	}
	return (i);
}

int	res_to_concat(int rl, char *res, char *concat)
{
	int	i;

	i = 0;
	if (rl > 0)
	{
		while (res[i])
		{
			concat[i] = res[i];
			++i;
		}
		free(res);
	}
	return (i);
}

char	*ft_strjoin(char *res, char *buf, int *rl)
{
	int		i;
	int		j;
	int		len;
	char	*concat;
	int		bl;

	bl = check_nl(buf);
	len = bl + *rl;
	concat = (char *)malloc(len + 1);
	if (!concat)
	{
		if (res)
			free(res);
		return (0);
	}
	i = res_to_concat(*rl, res, concat);
	j = 0;
	while (buf[j] && j < bl)
	{
		concat[i + j] = buf[j];
		++j;
	}
	concat[i + j] = '\0';
	*rl = i + j;
	return (concat);
}

char	*write_remainder(char *buf)
{
	char	*rem;
	int		i;
	int		j;

	i = 0;
	while (buf[i] != '\n')
		++i;
	if (buf[++i] == '\0')
		return (0);
	j = 0;
	while (buf[i + j])
		++j;
	rem = (char *)malloc(j + 1);
	j = 0;
	while (buf[i + j])
	{
		rem[j] = buf[i + j];
		++j;
	}
	rem[j] = '\0';
	return (rem);
}
