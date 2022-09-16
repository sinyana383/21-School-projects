/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:13:43 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 16:14:17 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	set_pipe_fork(t_cmd *cmd, int pipes[2][2], t_info *for_cmd)
{
	if (cmd->next && pipe(pipes[for_cmd->i % 2]) == -1)
	{
		set_status(1);
		return (print_errno_error("pipe", NULL));
	}
	for_cmd->pid = fork();
	if (for_cmd->pid < 0)
	{
		set_status(1);
		return (print_errno_error("fork", NULL));
	}
	return (1);
}

static void	prev_cmd_check(t_cmd *cmd, t_info *for_cmd)
{
	int	status;

	status = -1;
	if (open_exit(cmd) < 0)
		status = 1;
	else if (!cmd->argvs)
	{
		if (files_prepare_fd(cmd->redirs, for_cmd->fd) < 0)
			status = 1;
		else
			status = 0;
	}
	if (status > -1)
	{
		set_status(status);
		exit(status);
	}
}

static int	run_cmds(t_cmd *cmd, int pipes[2][2], t_info *for_cmd)
{
	while (cmd)
	{
		if (cmd->type == CMD_PIPE)
		{
			cmd = cmd->next;
			continue ;
		}
		if (set_pipe_fork(cmd, pipes, for_cmd) < 0)
			return (-1);
		if (for_cmd->pid == 0)
		{
			prev_cmd_check(cmd, for_cmd);
			if (check_and_exe_builtin(cmd, pipes, for_cmd->i) < 0)
				execve_cmd(cmd, for_cmd->i, pipes);
		}
		if (cmd->argvs)
			close_pipe(pipes, for_cmd->i, (cmd->next == NULL));
		++(for_cmd->i);
		cmd = cmd->next;
	}
	return (0);
}

int	execute_cmds(t_cmd *cmd, int pipes[2][2])
{
	t_info	for_cmd;

	for_cmd.i = 0;
	init_pipe(pipes);
	if (run_cmds(cmd, pipes, &for_cmd) < 0)
		return (-1);
	waitpid(for_cmd.pid, &(for_cmd.status), 0);
	for_cmd.status = WEXITSTATUS(for_cmd.status);
	set_status(for_cmd.status);
	for_cmd.pid = 0;
	while (for_cmd.pid >= 0)
		for_cmd.pid = wait(NULL);
	errno = 0;
	return (for_cmd.status);
}
