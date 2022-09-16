/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:04:48 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 14:54:20 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_sleep(unsigned long mls)
{
	struct timeval	tp;
	unsigned long	start;

	gettimeofday(&tp, NULL);
	start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	while ((tp.tv_sec * 1000 + tp.tv_usec / 1000) - start < mls)
	{
		usleep(50);
		gettimeofday(&tp, NULL);
	}
}

int	print_act(char *s, t_phil_process *pprocess, int isdead)
{
	t_data			*data;

	data = (t_data *)pprocess->data;
	sem_wait(data->std_out);
	print_unsigned_number(gettime_to_mls() - data->start, 10, 'a');
	write(1, " ", 1);
	print_unsigned_number(pprocess->number, 10, 'a');
	write(1, " ", 1);
	ft_putstr(s);
	write(1, "\n", 1);
	if (isdead == 1)
		exit(-1);
	sem_post(data->std_out);
	return (0);
}

void	eating(t_phil_process *pprocess, t_data *data)
{
	sem_wait(data->forks);
	print_act("has taken a fork", pprocess, 0);
	sem_wait(data->forks);
	print_act("has taken a fork", pprocess, 0);
	print_act("is eating", pprocess, 0);
	sem_wait(pprocess->last_eating);
	pprocess->last_eat = gettime_to_mls();
	sem_post(pprocess->last_eating);
	my_sleep(data->input_data[EAT_TIME]);
	pprocess->eat_times += 1;
	sem_post(data->forks);
	sem_post(data->forks);
	if (data->input_data[EAT_TIMES] > -1 && \
	pprocess->eat_times >= data->input_data[EAT_TIMES])
		exit(0);
}

void	*death_and_life_cheack(void	*argc)
{
	t_phil_process	*pprocess;
	t_data			*data;

	pprocess = (t_phil_process *)argc;
	data = pprocess->data;
	while (1)
	{
		sem_wait(pprocess->last_eating);
		if (gettime_to_mls() - pprocess->last_eat \
			>= (unsigned long)data->input_data[DIE_TIME])
		{
			pprocess->is_dead = 1;
			print_act("died", pprocess, 1);
			sem_post(pprocess->last_eating);
			return (NULL);
		}
		sem_post(pprocess->last_eating);
		usleep(100);
	}
	return (NULL);
}

int	act(t_phil_process *pprocess)
{
	t_data	*data;

	data = (t_data *)pprocess->data;
	pprocess->last_eat = gettime_to_mls();
	if (pthread_create(&(pprocess->thread), NULL, \
	death_and_life_cheack, pprocess) != 0)
		exit(ft_putstr_error("thread create error\n"));
	pthread_detach(pprocess->thread);
	while (1)
	{
		eating(pprocess, data);
		print_act("is sleeping", pprocess, 0);
		my_sleep(data->input_data[SLEEP_TIME]);
		print_act("is thinking", pprocess, 0);
	}
	exit(-1);
}
