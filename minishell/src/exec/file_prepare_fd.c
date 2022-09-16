/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_prepare_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:16:37 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:16:40 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	open_files(char *str_content, char *file_str, int fd[2])
{
	if (m_strncmp(str_content, ">>", ft_strlen(">>")) == 0)
	{
		if (fd[1] > STDERR_FILENO)
			close(fd[1]);
		fd[1] = open(file_str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd[1] < 0)
			return (print_errno_error(file_str, NULL));
	}
	else if (m_strncmp(str_content, "<", ft_strlen("<")) == 0)
	{
		if (fd[0] > STDERR_FILENO)
			close(fd[0]);
		fd[0] = open(file_str, O_RDONLY);
		if (fd[0] < 0)
			return (print_errno_error(file_str, NULL));
	}
	else if (m_strncmp(str_content, ">", ft_strlen(">")) == 0)
	{
		if (fd[1] > STDERR_FILENO)
			close(fd[1]);
		fd[1] = open(file_str, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		if (fd[1] < 0)
			return (print_errno_error(file_str, NULL));
	}
	return (1);
}

static int	open_heredoc(int fd[2], char *file_str)
{
	int		heredoc_pipe[2];

	if (fd[0] > STDERR_FILENO)
		close(fd[0]);
	if (pipe(heredoc_pipe) < 0)
		return (print_errno_error("pipe", NULL));
	write(heredoc_pipe[1], file_str, ft_strlen(file_str));
	close(heredoc_pipe[1]);
	fd[0] = heredoc_pipe[0];
	return (1);
}

int	files_prepare_fd(t_list *redirs, int fd[2])
{
	char	*str_content;
	char	*file_str;

	while (redirs)
	{
		str_content = ((t_c_token *)redirs->content)->str;
		file_str = ((t_c_token *)(redirs->next)->content)->str;
		if (m_strncmp(str_content, "<<", ft_strlen("<<")) == 0)
		{
			if (open_heredoc(fd, file_str) < 0)
				return (-1);
		}
		else
		{
			if (open_files(str_content, file_str, fd) < 0)
				return (-1);
		}
		redirs = redirs->next->next;
	}
	return (0);
}
