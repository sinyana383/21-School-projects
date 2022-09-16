/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:58:21 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:09:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	chage_pwd_oldpwd(char *old_path)
{
	char		*path;
	int			status;

	status = 0;
	path = getcwd(NULL, 0);
	if (!path)
	{
		free(old_path);
		print_errno_error("cd", "malloc");
		return (1);
	}
	if (change_or_add_var("OLDPWD", old_path, 0, "cd") < 0 || \
	change_or_add_var("PWD", path, 0, "cd") < 0)
		status = 1;
	free(path);
	free(old_path);
	return (status);
}

int	built_cd(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	t_list		*argvs;
	char		*old_path;

	if (build_prepare(cmd, fd_save, pipes, i) < 0)
		return (1);
	argvs = cmd->argvs;
	argvs = argvs->next;
	old_path = getcwd(NULL, 0);
	if (!old_path)
	{
		print_errno_error("cd", "getcwd");
		return (1);
	}
	if (chdir(con_token(argvs)->str) < 0)
	{
		free(old_path);
		print_errno_error("cd", "chdir");
		return (1);
	}
	return (chage_pwd_oldpwd(old_path));
}
