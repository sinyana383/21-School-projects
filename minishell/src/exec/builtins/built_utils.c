/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:35:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:09:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_c_token	*con_token(t_list *lst)
{
	return (lst->content);
}

static void	dup2_and_close(int fd[2])
{
	if (fd[0] > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] > 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

int	build_prepare(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	int	fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd_save[0] = dup(STDIN_FILENO);
	fd_save[1] = dup(STDOUT_FILENO);
	if (fd_save[0] < 0 || fd_save[1] < 0)
		return (print_errno_error("dup", NULL));
	if (i > 0 || cmd->next)
		pipes_prepare_fd(fd, pipes, i, (cmd->argvs == NULL));
	if (files_prepare_fd(cmd->redirs, fd) < 0)
	{
		close_fd(fd);
		return (-1);
	}
	dup2_and_close(fd);
	return (1);
}

int	build_finish(int fd_save[2])
{
	if (fd_save[0] > 0)
		dup2(fd_save[0], STDIN_FILENO);
	if (fd_save[1] > 0)
		dup2(fd_save[1], STDOUT_FILENO);
	return (1);
}
