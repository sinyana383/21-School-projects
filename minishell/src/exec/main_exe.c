/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:22 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 15:37:30 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	executor(t_cmd	*cmds)
{
	int	pipes[2][2];
	int	exit_status;

	exit_status = -1;
	if (!(open_all_dollars(cmds) < 0) && !(connect_all(cmds) < 0))
	{
		if (cmds->next)
			exit_status = execute_cmds(cmds, pipes);
		else
			exit_status = one_cmd_exe(cmds);
	}
	if (exit_status < 0)
		set_status(1);
	else
		set_status(exit_status);
	return (0);
}
