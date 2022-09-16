/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:40:29 by ddurrand          #+#    #+#             */
/*   Updated: 2021/11/15 15:53:43 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_and_step(int fd, char **buf)
{
	int	check;

	*buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!(*buf))
		return (-1);
	check = read(fd, (*buf), BUFFER_SIZE);
	if (check <= 0 || check > BUFFER_SIZE)
	{
		free(*buf);
		return (check);
	}
	(*buf)[check] = '\0';
	return (check);
}

int	check_rem_and_start(int fd, char **rem, char **buf)
{
	int	check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (*rem)
	{
		*buf = *rem;
		*rem = 0;
		return (1);
	}
	check = check_and_step(fd, buf);
	return (check);
}

int	check_res(char *res, char *buf, char **rem, int res_len)
{
	if (!res)
	{
		free(buf);
		return (-1);
	}
	if (res[res_len - 1] == '\n')
	{
		*rem = write_remainder(buf);
		free(buf);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*buf;
	char		*res;
	int			res_len;
	int			check;

	res = NULL;
	res_len = 0;
	check = check_rem_and_start(fd, &rem, &buf);
	while (check > 0)
	{
		res = ft_strjoin(res, buf, &res_len);
		check = check_res(res, buf, &rem, res_len);
		if (check == 1)
			return (res);
		if (check == -1)
			return (NULL);
		free(buf);
		check = check_and_step(fd, &buf);
	}
	if (check == 0)
		return (res);
	if (res)
		free(res);
	return (NULL);
}
