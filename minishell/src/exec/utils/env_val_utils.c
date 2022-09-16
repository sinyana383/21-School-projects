/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_val_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:37:51 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:14:20 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_and_set_val(char **val, char *str, int len)
{
	unsigned long		i;
	int					find;

	i = 0;
	find = 0;
	while (g_env[i] && !find)
	{
		find = ((m_strncmp(str, g_env[i], len)) == 0 && (g_env[i][len] == '='));
		++i;
	}
	if (!find)
		return (0);
	i--;
	*val = ft_strdup(ft_strchr(g_env[i], '=') + 1);
	if (!*val)
		return (print_errno_error("malloc", NULL));
	return (1);
}

int	open_env_val(char **val, char *str, int *i)
{
	int	len;

	len = 0;
	while (str[++len])
	{
		if (!((str[len] >= '0' && str[len] <= '9') || str[len] == '_' || \
		(str[len] >= 'a' && str[len] <= 'z') || (str[len] >= 'A' \
		&& str[len] <= 'Z')))
			break ;
	}
	*i += len;
	if (len == 1)
	{
		*val = ft_strdup("$");
		if (!*val)
			return (print_errno_error("malloc", NULL));
		return (1);
	}
	len -= 1;
	return (find_and_set_val(val, str + 1, len));
}
