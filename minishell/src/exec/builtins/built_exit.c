/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:23:43 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 14:25:22 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_str_digit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		++i;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	built_exit(t_cmd *cmd)
{
	t_list	*argvs;

	argvs = cmd->argvs;
	argvs = argvs->next;
	if (!argvs)
		exit (*get_status_adress());
	if (is_str_digit(con_token(argvs)->str) == 0)
	{
		just_print_error("exit", NULL, \
			"numeric argument required");
		exit (1);
	}
	if (argvs->next)
	{
		just_print_error("exit", NULL, \
			"too many arguments");
		exit (1);
	}
	exit (ft_atoi(con_token(argvs)->str));
}

int	only_exit(t_cmd *cmd, char *status)
{
	t_list	*argvs;

	argvs = cmd->argvs->next;
	write(STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
	if (!argvs)
	{
		*status = *get_status_adress();
		return (1);
	}
	*status = 1;
	if (is_str_digit(con_token(argvs)->str) == 0)
	{
		just_print_error("exit", con_token(argvs)->str, \
			"numeric argument required");
		*status = (char)(-1);
		return (1);
	}
	if (argvs->next)
	{
		just_print_error("exit", NULL, \
			"too many arguments");
		return (-1);
	}
	*status = ft_atoi(con_token(argvs)->str);
	return (1);
}
