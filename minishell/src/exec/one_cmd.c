/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:34:05 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 15:46:05 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <readline/history.h>
#include <readline/readline.h>

static int	only_exit_and_exit(t_cmd *cmd, int *status)
{
	char	c_status;

	if (only_exit(cmd, &c_status) < 0)
	{
		*status = (int)c_status;
		return (1);
	}
	free_strs(&g_env);
	ft_lstclear_cmd(&cmd, cmd_destroy);
	rl_clear_history();
	exit((int)c_status);
	return (0);
}

static int	no_argvs_or_exit(t_cmd *cmd, int fd[2], int *status)
{
	if (open_exit(cmd) < 0)
		return (-1);
	if (!cmd->argvs)
	{
		if (files_prepare_fd(cmd->redirs, fd) < 0)
		{
			close_fd(fd);
			*status = 1;
		}
		else
			*status = 0;
		set_status(*status);
	}
	else if (ft_strncmp(con_token(cmd->argvs)->str, "exit", 5) == 0)
		return (only_exit_and_exit(cmd, status));
	return (1);
}

int	one_cmd_exe(t_cmd *cmd)
{
	int	status;
	int	pid;
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	status = -1;
	if (no_argvs_or_exit(cmd, fd, &status) < 0)
		return (-1);
	if (status >= 0)
		return (status);
	status = check_and_exe_builtin(cmd, NULL, 0);
	if (status < 0)
	{
		pid = fork();
		if (pid == -1)
			return (print_errno_error("fork", NULL));
		if (pid == 0)
			execve_cmd(cmd, 0, NULL);
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	return (status);
}
