/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:08:47 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 13:29:42 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_for_syntax(char *var, char *builtin)
{
	int	only_digits;
	int	i;

	i = -1;
	only_digits = 1;
	while (var[++i])
	{
		if (!((var[i] >= '0' && var[i] <= '9') || var[i] == '_' || \
		(var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' \
		&& var[i] <= 'Z')))
			return (just_print_error(builtin, var, \
			"not a valid identifier"));
		if (!((var[i] >= '0' && var[i] <= '9')))
			only_digits = 0;
	}
	if (only_digits)
		return (just_print_error(builtin, var, \
		"not a valid identifier"));
	return (1);
}

char	*get_spece_for_newvar(char *var, int *len, char *val, char *name)
{
	char	*res;

	if (check_for_syntax(var, name) < 0)
		return (NULL);
	*len = ft_strlen(var);
	if (val)
		*len += ft_strlen(val) + 1;
	res = malloc(sizeof(char) * (*len + 1));
	if (!res)
		print_errno_error(name, "malloc");
	return (res);
}

char	*create_env_var(char *var, char *val, char *name)
{
	char	*new_var;
	int		len;
	int		i;
	int		j;

	j = 0;
	new_var = get_spece_for_newvar(var, &len, val, name);
	if (!new_var)
		return (NULL);
	i = -1;
	while (var[++i])
		new_var[i] = var[i];
	if (val)
	{
		new_var[i++] = '=';
		j = -1;
		while (val[++j])
			new_var[i + j] = val[j];
	}
	new_var[i + j] = '\0';
	return (new_var);
}

int	add_var(char *variable, char *name)
{
	int		len;
	char	**new_env;

	len = 0;
	if (!variable)
		return (-1);
	while (g_env[len])
		++len;
	new_env = malloc(sizeof(char *) * (len + 1 + 1));
	if (!new_env)
	{
		free(variable);
		return (print_errno_error(name, "malloc"));
	}
	len = -1;
	while (g_env[++len])
		new_env[len] = g_env[len];
	new_env[len] = variable;
	new_env[len + 1] = NULL;
	free(g_env);
	g_env = new_env;
	return (1);
}

int	change_or_add_var(char *var, char *val, int is_add, char *name)
{
	int		i;
	char	*var_to_change;

	i = -1;
	if (!g_env)
		return (just_print_error(name, NULL, \
		"env is not set up"));
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], var, ft_strlen(var) + 1) == '\0' || \
		ft_strncmp(g_env[i], var, ft_strlen(var) + 1) == '=')
			break ;
	}
	if (!g_env[i])
	{
		if (is_add)
			return (add_var(create_env_var(var, val, name), name));
		return (0);
	}
	var_to_change = create_env_var(var, val, name);
	if (!var_to_change)
		return (print_errno_error(name, "malloc"));
	free(g_env[i]);
	g_env[i] = var_to_change;
	return (1);
}
