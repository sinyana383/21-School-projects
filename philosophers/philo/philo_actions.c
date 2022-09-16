/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:03:20 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:47 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	print_act(char *s, t_phil_thread *pthread, int isdead)
{
	t_data			*data;

	data = (t_data *)pthread->data;
	pthread_mutex_lock(&(data->std_out));
	if (is_dead_cheack(data) && isdead == 0)
	{
		pthread_mutex_unlock(&(data->std_out));
		return (0);
	}
	print_unsigned_number(gettime_to_mls() - data->start, 10, 'a');
	write(1, " ", 1);
	print_unsigned_number(pthread->number, 10, 'a');
	write(1, " ", 1);
	ft_putstr(s);
	write(1, "\n", 1);
	pthread_mutex_unlock(&(data->std_out));
	return (0);
}

void	lock_forks(t_phil_thread *phil_thread)
{
	pthread_mutex_lock(phil_thread->right_fork);
	print_act("has taken a fork", phil_thread, 0);
	pthread_mutex_lock(phil_thread->left_fork);
	print_act("has taken a fork", phil_thread, 0);
}

void	eating(t_phil_thread *phil_thread, t_data *data)
{
	lock_forks(phil_thread);
	pthread_mutex_lock(&(data->last_eating));
	print_act("is eating", phil_thread, 0);
	phil_thread->last_eat = gettime_to_mls();
	pthread_mutex_unlock(&(data->last_eating));
	my_sleep(data->input_data[EAT_TIME]);
	pthread_mutex_lock(&data->eat_times_check);
	phil_thread->eat_times += 1;
	pthread_mutex_unlock(&data->eat_times_check);
	pthread_mutex_unlock(phil_thread->right_fork);
	pthread_mutex_unlock(phil_thread->left_fork);
}

void	*act(void *args)
{
	t_phil_thread	*phil_thread;
	t_data			*data;

	phil_thread = (t_phil_thread *)args;
	data = (t_data *)phil_thread->data;
	if (data->input_data[PHIL_NB] == 1)
	{
		print_act("has taken a fork", phil_thread, 0);
		while (is_dead_cheack(data) == 0)
			;
		return (NULL);
	}
	if ((phil_thread->number) % 2 != 0)
		usleep(8000);
	while (1)
	{
		if (is_dead_cheack(data))
			return (NULL);
		eating(phil_thread, data);
		print_act("is sleeping", phil_thread, 0);
		my_sleep(data->input_data[SLEEP_TIME]);
		print_act("is thinking", phil_thread, 0);
	}
	return (NULL);
}
