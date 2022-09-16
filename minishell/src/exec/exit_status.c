/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:43:20 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:49:44 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	*get_status_adress(void)
{
	static int	status;

	return (&status);
}

void	set_status(int new_status)
{
	int	*status;

	status = get_status_adress();
	*status = new_status;
}

static int	set_new_line_and_status(char **new_line, char *str, char **status)
{
	*new_line = ft_strdup("");
	if (!*new_line)
		return (print_errno_error("malloc", NULL));
	*new_line = ft_strjoin_val(*new_line, str, \
	m_strnstr(str, "$?", 2) - str);
	if (!*new_line)
		return (print_errno_error("malloc", NULL));
	*status = ft_itoa(*(get_status_adress()));
	if (!*status)
	{
		free(*new_line);
		return (print_errno_error("malloc", NULL));
	}
	return (1);
}

static int	opening(t_list *lst)
{
	char		*str;
	char		*new_line;
	char		*status;

	while (lst)
	{
		str = con_token(lst)->str;
		while (m_strnstr(str, "$?", 2))
		{
			if (set_new_line_and_status(&new_line, str, &status) < 0)
				return (-1);
			new_line = ft_strjoin_val(new_line, status, ft_strlen(status));
			free(status);
			if (!new_line)
				return (print_errno_error("malloc", NULL));
			con_token(lst)->str = new_line;
			free(str);
			str = con_token(lst)->str;
		}
		lst = lst->next;
	}
	return (1);
}

int	open_exit(t_cmd *cmd)
{
	if (cmd->argvs)
	{
		if (opening(cmd->argvs) < 0)
			return (-1);
	}
	if (cmd->redirs)
	{
		if (opening(cmd->redirs) < 0)
			return (-1);
	}
	return (1);
}
