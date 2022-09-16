/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:50:38 by ddurrand          #+#    #+#             */
/*   Updated: 2021/11/15 16:12:55 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	char	*concat;
	int		bl;

	bl = 0;
	while (buf[bl] && buf[bl] != '\n')
		++bl;
	bl += (buf[bl] == '\n');
	concat = (char *)malloc(bl + *rl + 1);
	if (!concat)
	{
		if (res)
			free(res);
		return (0);
	}
	i = res_to_concat(*rl, res, concat);
	j = -1;
	while (buf[++j] && j < bl)
		concat[i + j] = buf[j];
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

t_list	*ft_lstnew(int fd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->fd = fd;
	new->rem = 0;
	new->next = 0;
	return (new);
}

void	ft_lstdel(t_list **start, int fd)
{
	t_list	*find;
	t_list	**prev;

	if (!start)
		return ;
	if (!(*start))
		return ;
	find = *start;
	prev = start;
	while (find->fd != fd && find)
	{
		prev = &(find->next);
		find = find->next;
	}
	*prev = find->next;
	find->rem = 0;
	free(find);
	if (find == *start)
		*start = NULL;
}
