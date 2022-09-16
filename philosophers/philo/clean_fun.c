/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:52:10 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:39 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all_malloc(t_data *data)
{
	free(data->phil_threads);
	free(data->forks);
}

void	clean_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
		pthread_mutex_destroy(data->forks + i);
	pthread_mutex_destroy(&data->std_out);
	pthread_mutex_destroy(&data->last_eating);
	pthread_mutex_destroy(&data->is_dead_cheack);
	pthread_mutex_destroy(&data->eat_times_check);
	clean_all_malloc(data);
}

int	mutex_part(t_data *data)
{
	if (pthread_mutex_init(&(data->eat_times_check), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->std_out));
		pthread_mutex_destroy(&(data->last_eating));
		clean_all_malloc(data);
		return (ft_putstr_error("mutex init error\n"));
	}
	if (pthread_mutex_init(&(data->is_dead_cheack), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->eat_times_check));
		pthread_mutex_destroy(&(data->std_out));
		pthread_mutex_destroy(&(data->last_eating));
		clean_all_malloc(data);
		return (ft_putstr_error("mutex init error\n"));
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data->std_out), NULL) != 0)
	{
		clean_all_malloc(data);
		return (ft_putstr_error("mutex init error\n"));
	}
	if (pthread_mutex_init(&(data->last_eating), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->std_out));
		clean_all_malloc(data);
		return (ft_putstr_error("mutex init error\n"));
	}
	return (mutex_part(data));
}
