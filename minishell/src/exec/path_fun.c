/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:36:57 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:23:43 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/types.h>
#include <sys/stat.h>

static void	path_free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

static int	accessing(char *tmp_res, char **res, char **paths, char *program)
{
	if (access(tmp_res, X_OK) == 0)
	{
		*res = tmp_res;
		path_free_strs(paths);
		return (1);
	}
	else if (errno != ENOENT)
	{
		free(tmp_res);
		path_free_strs(paths);
		return (print_errno_error(program, NULL));
	}
	return (0);
}

int	path_searching(char **paths, char *program, char **res)
{
	int		i;
	char	*tmp_res;
	int		status;

	i = -1;
	while (paths[++i])
	{
		tmp_res = ft_strjoin_path(paths[i], program);
		if (!tmp_res)
		{
			path_free_strs(paths);
			print_errno_error("malloc", NULL);
			return (-1);
		}
		status = accessing(tmp_res, res, paths, program);
		if (status < 0 || status == 1)
			return (status);
		free(tmp_res);
		tmp_res = 0;
	}
	just_print_error(program, NULL, "command not found");
	path_free_strs(paths);
	return (-1);
}

static int	program_path_checking(char *program, char **path)
{
	struct stat	info;

	if (!*program)
		return (just_print_error(program, NULL, \
		"command not found"));
	stat(program, &info);
	if (S_ISDIR(info.st_mode))
		return (just_print_error(program, NULL, \
		"is a directory"));
	if (access(program, X_OK) == 0)
	{
		if (!ft_strchr(program, '/'))
			return (just_print_error(program, NULL, \
		"command not found"));
		*path = ft_strdup(program);
		return (1);
	}
	else if (errno != ENOENT || ft_strchr(program, '/'))
		return (print_errno_error(program, NULL));
	return (0);
}

int	set_program_path(char **env, char *program, char **path)
{
	char	*res;
	char	*whole_path;
	char	**paths;
	int		i;

	i = program_path_checking(program, path);
	if (i < 0 || i == 1)
		return (i);
	whole_path = 0;
	i = -1;
	while (env[++i] && !whole_path)
		whole_path = m_strnstr(env[i], "PATH=", 5);
	if (!whole_path)
		return (print_errno_error(program, NULL));
	paths = my_ft_split(whole_path + 5, ':');
	if (!paths || !(*paths))
	{
		print_errno_error("malloc", NULL);
		return (-1);
	}
	if (path_searching(paths, program, &res) < 0)
		return (-1);
	*path = res;
	return (1);
}
