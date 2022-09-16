/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:35:54 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 15:53:28 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	set_pipe_closed(int *pipe_end)
{
	if (*pipe_end == -1)
		return (0);
	close(*pipe_end);
	*pipe_end = -1;
	return (1);
}

static void	close_all(int pipes[2][2])
{
	set_pipe_closed(&pipes[0][0]);
	set_pipe_closed(&pipes[0][1]);
	set_pipe_closed(&pipes[1][0]);
	set_pipe_closed(&pipes[1][1]);
}

int	close_pipe(int pipes[2][2], int i, int last)
{
	if (i == -1)
		close_all(pipes);
	else if (i == 0)
		set_pipe_closed(&pipes[0][1]);
	else if (last)
	{
		if (i % 2 == 1)
			set_pipe_closed(&pipes[0][0]);
		if (i % 2 == 0)
			set_pipe_closed(&pipes[1][0]);
	}
	else if (i % 2 == 0)
	{
		set_pipe_closed(&pipes[1][0]);
		set_pipe_closed(&pipes[0][1]);
	}
	else if (i % 2 == 1)
	{
		set_pipe_closed(&pipes[0][0]);
		set_pipe_closed(&pipes[1][1]);
	}
	return (0);
}

void	init_pipe(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

void	pipes_prepare_fd(int fd[2], int pipes[2][2], int i, int last)
{
	if (i == 0)
		fd[1] = pipes[0][1];
	else if (last)
	{
		if (i % 2 == 0)
			fd[0] = pipes[1][0];
		if (i % 2 == 1)
			fd[0] = pipes[0][0];
	}
	else if (i % 2 == 1)
	{
		fd[0] = pipes[0][0];
		fd[1] = pipes[1][1];
	}
	else if (i % 2 == 0)
	{
		fd[0] = pipes[1][0];
		fd[1] = pipes[0][1];
	}
}
