/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:33:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:09:29 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	del_index_from_env(int i)
{
	char	**new_env;
	int		del_index;
	int		j;

	del_index = i;
	while (g_env[i])
		++i;
	new_env = malloc(sizeof(char **) * (i + 1));
	if (!new_env)
		return (print_errno_error("unset", "malloc"));
	i = -1;
	j = 0;
	while (g_env[++i])
	{
		if (i != del_index)
			new_env[j++] = g_env[i];
	}
	new_env[j] = NULL;
	free(g_env[del_index]);
	free(g_env);
	g_env = new_env;
	return (1);
}

int	remove_var(char	*var)
{
	int		i;

	if (check_for_syntax(var, "unset") < 0)
		return (1);
	i = -1;
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], var, ft_strlen(var) + 1) == '\0' || \
		ft_strncmp(g_env[i], var, ft_strlen(var) + 1) == '=')
			break ;
	}
	if (!g_env[i])
		return (0);
	if (del_index_from_env(i) < 0)
		return (1);
	return (0);
}

int	built_unset(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	t_list		*argvs;
	char		*str;
	int			status;

	argvs = cmd->argvs;
	argvs = argvs->next;
	status = 0;
	if (build_prepare(cmd, fd_save, pipes, i) < 0)
		return (1);
	if (!argvs)
		return (0);
	while (argvs)
	{
		str = con_token(argvs)->str;
		if (ft_strncmp(str, "_=", 2) != 0)
			status = remove_var(str);
		argvs = argvs->next;
	}
	return (status);
}
