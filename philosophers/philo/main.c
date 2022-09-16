/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:55:45 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:44 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_cheack(t_data *data)
{
	pthread_mutex_lock(&(data->is_dead_cheack));
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&(data->is_dead_cheack));
		return (1);
	}
	if (data->eat_all == 1)
	{
		pthread_mutex_unlock(&(data->is_dead_cheack));
		return (-1);
	}
	pthread_mutex_unlock(&(data->is_dead_cheack));
	return (0);
}

unsigned long	gettime_to_mls(void)
{
	struct timeval	tp;
	unsigned long	res;

	gettimeofday(&tp, NULL);
	res = (unsigned long)(tp.tv_sec * 1000 + tp.tv_usec / 1000);
	return (res);
}

void	join_and_clean(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
		pthread_join(data->phil_threads[i].thread, NULL);
	clean_all(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (ft_putstr_error("wrong number of arguments\n"));
	if (initioizer(&data, argv, argc) < 0)
		return (-1);
	i = -1;
	data.start = gettime_to_mls();
	while (++i < data.input_data[PHIL_NB])
	{
		if (pthread_create(&(data.phil_threads[i].thread), \
		NULL, act, &data.phil_threads[i]) != 0)
		{
			clean_all(&data);
			return (ft_putstr_error("thread create error\n"));
		}
		pthread_mutex_lock(&(data.last_eating));
		data.phil_threads[i].last_eat = gettime_to_mls();
		pthread_mutex_unlock(&(data.last_eating));
	}
	dead_and_eat_all_checker(&data);
	join_and_clean(&data);
	return (1);
}
