/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:40:07 by ddurrand          #+#    #+#             */
/*   Updated: 2022/02/13 14:54:56 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	open_files(int *in, int *out, char **argv)
{
	*in = open(argv[1], O_RDONLY);
	if (*in < 0)
		perror(argv[1]);
	*out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (*out < 0)
		perror(argv[4]);
}

void	exe_cmd_in(t_pipe pipex, char *program, char **env)
{
	if (pipex.files[0] < 0)
		exit(EXIT_FAILURE);
	if (dup2(pipex.pipefd[1], STDOUT_FILENO) < 0)
		perror("dup2");
	if (close(pipex.pipefd[1]) < 0)
		perror("close");
	if (dup2(pipex.files[0], STDIN_FILENO))
		perror("dup2");
	pipex.argums = ft_split(program, ' ');
	if (!(pipex.argums))
		exit(EXIT_FAILURE);
	pipex.program_path = get_program_path(env, pipex.argums[0]);
	if (!pipex.program_path)
	{
		free_strs(pipex.argums);
		exit(EXIT_FAILURE);
	}
	execve(pipex.program_path, pipex.argums, env);
	perror("execve");
}

void	exe_cmd_out(t_pipe pipex, char *program, char **env)
{
	if (pipex.files[1] < 0)
		exit(EXIT_FAILURE);
	if (dup2(pipex.pipefd[0], STDIN_FILENO) < 0)
		perror("dup2");
	if (close(pipex.pipefd[1]) < 0)
		perror("close");
	if (dup2(pipex.files[1], STDOUT_FILENO) < 0)
		perror("dup2");
	pipex.argums = ft_split(program, ' ');
	if (!(pipex.argums))
		exit(EXIT_FAILURE);
	pipex.program_path = get_program_path(env, pipex.argums[0]);
	if (!pipex.program_path)
	{
		free_strs(pipex.argums);
		exit(EXIT_FAILURE);
	}
	execve(pipex.program_path, pipex.argums, env);
	perror("execve");
}

void	pre_start(int argc, char **argvs, t_pipe *pipex)
{
	if (argc != 5)
	{
		print_prog_error("wrong arguments number");
		exit(EXIT_FAILURE);
	}
	open_files(&((*pipex).files[0]), &((*pipex).files[1]), argvs);
	if (pipe((*pipex).pipefd) < 0)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argvs, char **env)
{
	t_pipe	pipex;
	int		status;

	pre_start(argc, argvs, &pipex);
	pipex.id[0] = fork();
	if (pipex.id[0] < 0)
		perror("fork");
	if (!pipex.id[0])
		exe_cmd_in(pipex, argvs[2], env);
	pipex.id[1] = fork();
	if (pipex.id[1] < 0)
		perror("fork");
	if (!pipex.id[1])
		exe_cmd_out(pipex, argvs[3], env);
	if (close(pipex.pipefd[1]) < 0)
		perror("close");
	if (waitpid(pipex.id[1], &status, 0) < 0)
		perror("waitpid id2");
	exit(WEXITSTATUS(status));
}
