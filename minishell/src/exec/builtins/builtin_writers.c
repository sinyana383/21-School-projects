/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_writers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:46:39 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 14:15:32 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	built_echo(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	t_list	*argvs;
	int		option_n;

	argvs = cmd->argvs;
	argvs = argvs->next;
	option_n = 0;
	if (build_prepare(cmd, fd_save, pipes, i) < 0)
		return (1);
	while (argvs && !ft_strncmp(con_token(argvs)->str, "-n", 3))
	{
		option_n = 1;
		argvs = argvs->next;
	}
	while (argvs && con_token(argvs)->str)
	{
		write(STDOUT_FILENO, con_token(argvs)->str, \
		ft_strlen(con_token(argvs)->str));
		if (argvs->next && con_token(argvs->next)->str)
			write(STDOUT_FILENO, " ", 1);
		argvs = argvs->next;
	}
	if (!option_n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	built_pwd(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	char	*buf;

	if (build_prepare(cmd, fd_save, pipes, i) < 0)
		return (1);
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		print_errno_error("pwd", "getcwd");
		return (1);
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (0);
}

int	built_env(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	int		iter;

	if (build_prepare(cmd, fd_save, pipes, i) < 0)
		return (1);
	iter = -1;
	if (!g_env)
	{
		just_print_error(NULL, NULL, "environment isn't set up");
		return (1);
	}
	while (g_env[++iter])
	{
		if (ft_strchr(g_env[iter], '='))
		{
			write(STDOUT_FILENO, g_env[iter], ft_strlen(g_env[iter]));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (0);
}

int	check_and_exe_builtin(t_cmd *cmd, int pipes[2][2], int i)
{
	int	status;
	int	fd_saves[2];

	if (ft_strncmp(con_token(cmd->argvs)->str, "echo", 5) == 0)
		status = built_echo(cmd, fd_saves, pipes, i);
	else if (ft_strncmp(con_token(cmd->argvs)->str, "pwd", 4) == 0)
		status = built_pwd(cmd, fd_saves, pipes, i);
	else if (ft_strncmp(con_token(cmd->argvs)->str, "env", 4) == 0)
		status = built_env(cmd, fd_saves, pipes, i);
	else if (ft_strncmp(con_token(cmd->argvs)->str, "cd", 3) == 0)
		status = built_cd(cmd, fd_saves, pipes, i);
	else if (ft_strncmp(con_token(cmd->argvs)->str, "export", 7) == 0)
		status = built_export(cmd, fd_saves, pipes, i);
	else if (ft_strncmp(con_token(cmd->argvs)->str, "unset", 6) == 0)
		status = built_unset(cmd, fd_saves, pipes, i);
	else if (ft_strncmp(con_token(cmd->argvs)->str, "exit", 5) == 0)
		status = built_exit(cmd);
	else
		return (-1);
	build_finish(fd_saves);
	set_status(status);
	if (pipes)
		exit(status);
	return (status);
}
