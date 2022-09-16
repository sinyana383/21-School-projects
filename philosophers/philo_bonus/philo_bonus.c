/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:36:43 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 14:49:11 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	gettime_to_mls(void)
{
	struct timeval	tp;
	unsigned long	res;

	gettimeofday(&tp, NULL);
	res = (unsigned long)(tp.tv_sec * 1000 + tp.tv_usec / 1000);
	return (res);
}

void	kill_or_wait(int status, t_data *data)
{
	int	i;

	i = -1;
	while (status == 0 && ++i < data->input_data[PHIL_NB])
	{
		waitpid(-1, &status, 0);
		status >>= 8;
	}
	if (status == 255)
	{
		i = -1;
		while (++i < data->input_data[PHIL_NB])
			kill(data->phil_process->pid, SIGKILL);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		exit(ft_putstr_error("wrong number of arguments\n"));
	if (initioizer(&data, argv, argc) < 0)
		exit(-1);
	i = -1;
	data.start = gettime_to_mls();
	while (++i < data.input_data[PHIL_NB])
	{
		data.phil_process[i].pid = fork();
		if (data.phil_process[i].pid < 0)
		{
			ft_putstr_error("fork error\n");
			kill_or_wait(-1, &data);
			exit(-1);
		}
		if (data.phil_process[i].pid == 0)
			act(data.phil_process + i);
	}
	kill_or_wait(0, &data);
	exit (1);
}
