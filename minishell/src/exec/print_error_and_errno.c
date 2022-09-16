/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_errno.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:50:10 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/12 14:23:43 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	just_print_error(char *str1, char *str2, char *error_massage)
{
	ft_putstr_fd("minishell: ", 2);
	if (str1)
	{
		ft_putstr_fd(str1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str2)
	{
		ft_putstr_fd(str2, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error_massage)
		ft_putstr_fd(error_massage, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	print_errno_error(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	if (str1)
	{
		ft_putstr_fd(str1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str2)
	{
		ft_putstr_fd(str2, 2);
		ft_putstr_fd(": ", 2);
	}
	perror("");
	return (-1);
}
