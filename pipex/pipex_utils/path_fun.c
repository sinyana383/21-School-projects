/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:36:57 by ddurrand          #+#    #+#             */
/*   Updated: 2022/02/13 14:14:43 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

char	*path_searching(char **paths, char	*program)
{
	int		i;
	char	*res;

	i = -1;
	res = 0;
	while (paths[++i])
	{
		res = ft_strjoin_path(paths[i], program);
		if (!res)
		{
			free_strs(paths);
			return (0);
		}
		if (access(res, X_OK) == 0)
		{
			free_strs(paths);
			return (res);
		}
		free(res);
		res = 0;
	}
	perror(program);
	free_strs(paths);
	return (0);
}

char	*get_program_path(char **env, char *program)
{
	char	*res;
	char	*whole_path;
	char	**paths;
	int		i;

	i = 0;
	whole_path = 0;
	i = -1;
	while (env[++i] && !whole_path)
		whole_path = ft_strnstr(env[i], "PATH=", 5);
	if (!whole_path)
	{
		print_prog_error("no PATH variable was found\n");
		return (0);
	}
	paths = ft_split(whole_path + 5, ':');
	if (!paths || !(*paths))
		return (0);
	res = path_searching(paths, program);
	return (res);
}
