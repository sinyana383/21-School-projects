/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:36:32 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:16:14 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>

static char	**get_argvs_to_strs(t_list *argvs)
{
	t_list	*tmp;
	char	**str_argv;
	int		i;
	int		len;

	len = 0;
	tmp = argvs;
	while (tmp != NULL)
	{
		++len;
		tmp = tmp->next;
	}
	str_argv = malloc(sizeof (char *) * (len + 1));
	if (!str_argv)
		return (NULL);
	i = 0;
	while (argvs != NULL)
	{
		str_argv[i++] = ((t_c_token *)argvs->content)->str;
		argvs = argvs->next;
	}
	str_argv[i] = NULL;
	return (str_argv);
}

void	close_fd(int fd[2])
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

int	show_ctrlc(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDERR_FILENO, &termios_p))
		return (print_errno_error("tcgetattr", NULL));
	termios_p.c_lflag |= ECHOCTL;
	if (tcsetattr(STDERR_FILENO, TCSANOW, &termios_p))
		return (print_errno_error("tcsetattr", NULL));
	return (1);
}

static void	prepare_execve(t_cmd *cmd, int i, int pipes[2][2])
{
	int			fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (i > 0 || cmd->next)
		pipes_prepare_fd(fd, pipes, i, (cmd->next == NULL));
	if (files_prepare_fd(cmd->redirs, fd) < 0)
	{
		close_fd(fd);
		exit (1);
	}
	if (fd[0] > 2)
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] > 2)
		dup2(fd[1], STDOUT_FILENO);
	close_fd(fd);
	if (i > 0 || cmd->next)
		close_pipe(pipes, -1, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	show_ctrlc();
}

int	execve_cmd(t_cmd *cmd, int i, int pipes[2][2])
{
	char		**str_argvs;
	char		*path;

	prepare_execve(cmd, i, pipes);
	str_argvs = get_argvs_to_strs(cmd->argvs);
	if (!str_argvs)
	{
		print_errno_error("malloc", NULL);
		set_status(1);
		exit(1);
	}
	if (set_program_path(g_env, str_argvs[0], &path) < 0)
		exit (127);
	execve(path, str_argvs, g_env);
	print_errno_error(str_argvs[0], NULL);
	free(path);
	free(str_argvs);
	exit (1);
}
