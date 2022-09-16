/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:41:40 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/20 13:52:38 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	read_all(void)
{
	char	a;
	int		check;

	check = 1;
	while (check > 0 && a != '\n')
		check = read(0, &a, 1);
}

void	clear_str(char	*str, int n)
{
	while (--n >= 0)
		str[n] = '\0';
}

int	init_malloc(char **action, int *check)
{
	*action = malloc(sizeof(char) * 6 + 1);
	if (!*action)
		return (-1);
	clear_str(*action, 7);
	*check = 1;
	return (1);
}

int	free_str_and_return(char *str, int r)
{
	free(str);
	return (r);
}

int	take_actions(t_list **a, t_list **b)
{
	char	*action;
	int		check;
	char	*run;

	if (init_malloc(&action, &check) < 0)
		return (-1);
	while (check > 0)
	{
		run = action;
		check = read(0, run, 1);
		while (check > 0 && *run != '\n' && run - action <= 3)
			check = read(0, ++run, 1);
		if (check < 1 || *run != '\n' || run - action > 3)
		{
			if (check > 0 && *run != '\n')
				read_all();
			if (check == 0 && run - action == 0)
				return (free_str_and_return(action, 1));
			return (free_str_and_return(action, -1));
		}
		if (make_act(action, a, b) < 0)
			return (free_str_and_return(action, -1));
		clear_str(action, 7);
	}
	return (free_str_and_return(action, 1));
}
