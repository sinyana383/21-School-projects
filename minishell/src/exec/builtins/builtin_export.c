/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:12:27 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:26:36 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	export_write(char **tmp_env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (tmp_env[++i])
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		tmp = ft_strchr(tmp_env[i], '=');
		if (!tmp)
			write(STDOUT_FILENO, tmp_env[i], ft_strlen(tmp_env[i]));
		else
		{
			write(STDOUT_FILENO, tmp_env[i], tmp - tmp_env[i]);
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, tmp + 1, ft_strlen(tmp + 1));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}

int	compare_two_vars(char *str1, char *str2, int *res)
{
	char	*var1;
	char	*var2;
	char	*c;

	var1 = ft_strdup(str1);
	if (!var1)
		return (print_errno_error("export", "malloc"));
	var2 = ft_strdup(str2);
	if (!var2)
	{
		free(var1);
		return (print_errno_error("export", "malloc"));
	}
	c = ft_strchr(var1, '=');
	if (c)
		*c = '\0';
	c = ft_strchr(var2, '=');
	if (c)
		*c = '\0';
	*res = ft_strncmp(var1, var2, ft_strlen(var1) + 1);
	free(var1);
	free(var2);
	return (1);
}

int	sort_strings(char **strs, int len)
{
	char	*tmp;
	int		i;
	int		j;
	int		compare;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (compare_two_vars(strs[j], strs[j + 1], &compare) < 0)
				return (-1);
			if (compare > 0)
			{
				tmp = strs[j];
				strs[j] = strs[j + 1];
				strs[j + 1] = tmp;
			}
		}
	}
	return (1);
}

int	write_in_alphabet(void)
{
	char	**tmp_env;
	int		i;

	i = 0;
	while (g_env[i])
		++i;
	tmp_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp_env)
	{
		print_errno_error("export", "malloc");
		return (1);
	}
	i = -1;
	while (g_env[++i])
		tmp_env[i] = g_env[i];
	tmp_env[i] = NULL;
	if (sort_strings(tmp_env, i) < 0)
	{
		free(tmp_env);
		return (1);
	}
	export_write(tmp_env);
	free(tmp_env);
	return (0);
}

int	built_export(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i)
{
	t_list		*argvs;
	char		*str;
	char		*val;
	int			status;

	argvs = cmd->argvs->next;
	status = 0;
	if (build_prepare(cmd, fd_save, pipes, i) < 0)
		return (1);
	if (!argvs)
		return (write_in_alphabet());
	while (argvs)
	{
		str = con_token(argvs)->str;
		if (ft_strncmp(str, "_=", 2) != 0)
		{
			val = ft_strchr(str, '=');
			if (val)
				*(val++) = '\0';
			if (change_or_add_var(str, val, 1, "export") < 0)
				return (1);
		}
		argvs = argvs->next;
	}
	return (0);
}
