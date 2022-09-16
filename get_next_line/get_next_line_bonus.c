/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 05:15:43 by ddurrand          #+#    #+#             */
/*   Updated: 2021/11/15 16:00:08 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		*rem = write_remainder (buf);
		free(buf);
		return (1);
	}
	return (0);
}

char	*get_line(int fd, char **rem)
{
	char		*buf;
	char		*res;
	int			res_len;
	int			check;

	res = NULL;
	res_len = 0;
	check = check_rem_and_start(fd, rem, &buf);
	while (check > 0)
	{
		res = ft_strjoin(res, buf, &res_len);
		check = check_res(res, buf, rem, res_len);
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

char	*get_next_line(int fd)
{
	static t_list	*start;
	t_list			*use;
	char			*res;

	if (!start)
		start = ft_lstnew(fd);
	if (!start)
		return (NULL);
	use = start;
	while (use->fd != fd && use)
	{
		if (use->next == 0)
		{
			use->next = ft_lstnew(fd);
			if (!(use->next))
				return (NULL);
		}
		use = use->next;
	}
	res = get_line(fd, &(use->rem));
	if (!res)
		ft_lstdel(&start, fd);
	return (res);
}
