/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_eat_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:12:42 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:40 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_cheack(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
	{
		pthread_mutex_lock(&(data->last_eating));
		if (gettime_to_mls() - data->phil_threads[i].last_eat \
		>= (unsigned long)data->input_data[DIE_TIME])
		{
			pthread_mutex_lock(&data->is_dead_cheack);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->is_dead_cheack);
			print_act("died", &(data->phil_threads[i]), 1);
		}
		pthread_mutex_unlock(&(data->last_eating));
		usleep(100);
		if (is_dead_cheack(data) > 0)
			return (-1);
	}
	return (1);
}

void	life_cheak(int	*i, t_data *data)
{
	*i = -1;
	while (++(*i) < data->input_data[PHIL_NB])
	{
		pthread_mutex_lock(&data->eat_times_check);
		if (data->phil_threads[*i].eat_times < \
		data->input_data[EAT_TIMES])
		{
			pthread_mutex_unlock(&data->eat_times_check);
			break ;
		}
		pthread_mutex_unlock(&data->eat_times_check);
	}
}

int	dead_and_eat_all_checker(t_data *data)
{
	int	i;

	while (1)
	{
		if (death_cheack(data) < 0)
			return (0);
		if (is_dead_cheack(data) != 0)
			return (0);
		if (data->input_data[EAT_TIMES] >= 0)
		{
			life_cheak(&i, data);
			if (i == data->input_data[PHIL_NB])
			{
				pthread_mutex_lock(&(data->is_dead_cheack));
				data->eat_all = 1;
				pthread_mutex_unlock(&(data->is_dead_cheack));
			}
		}
	}
	return (0);
}
