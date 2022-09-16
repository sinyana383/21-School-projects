/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:32:49 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:41 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, int *result)
{
	int		i;
	long	res;

	i = -1;
	res = 0;
	if (!str || *str == '\0')
		return (-1);
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res *= 10;
		res += str[i] - '0';
		if (res > 2147483647)
			return (-1);
	}
	*result = (int)res;
	return (1);
}

int	init_phils_and_forks(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
	{
		data->phil_threads[i].number = i + 1;
		data->phil_threads[i].data = data;
		data->phil_threads[i].last_eat = data->start;
		data->phil_threads[i].eat_times = 0;
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(data->forks + i);
			return (ft_putstr_error("mutex init error\n"));
		}
		if (i != 0)
		{
			data->phil_threads[i].right_fork = data->forks + i - 1;
			data->phil_threads[i].left_fork = data->forks + i;
		}
	}
	data->phil_threads[0].right_fork = data->forks + i - 1;
	data->phil_threads[0].left_fork = data->forks;
	return (1);
}

int	get_and_check_argv(t_data *data, char **av, int ac)
{
	int	i;

	i = 0;
	if (ac != 6)
		data->input_data[EAT_TIMES] = -1;
	while (++i < ac)
	{
		if (ft_atoi(av[i], &(data->input_data[i - 1])) < 0)
			return (ft_putstr_error("wrong param value\n"));
		if (data->input_data[i - 1] <= 0)
			return (ft_putstr_error("wrong param value\n"));
	}
	return (1);
}

int	malloc_section(t_data *data)
{
	data->phil_threads = (t_phil_thread *)malloc(\
	sizeof(t_phil_thread) * data->input_data[PHIL_NB]);
	if (!(data->phil_threads))
		return (ft_putstr_error("malloc error\n"));
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) \
	* data->input_data[PHIL_NB]);
	if (!(data->forks))
	{
		free(data->phil_threads);
		return (ft_putstr_error("malloc error\n"));
	}
	return (1);
}

int	initioizer(t_data *data, char **av, int ac)
{
	data->is_dead = 0;
	data->eat_all = 0;
	if (get_and_check_argv(data, av, ac) < 0)
		return (-1);
	if (malloc_section(data) < 0)
		return (-1);
	if (init_mutex(data) < 0)
		return (-1);
	if (init_phils_and_forks(data) < 0)
	{
		pthread_mutex_destroy(&(data->std_out));
		pthread_mutex_destroy(&(data->last_eating));
		pthread_mutex_destroy(&(data->eat_times_check));
		clean_all_malloc(data);
		return (-1);
	}
	return (1);
}
