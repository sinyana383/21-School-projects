/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiolizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:58:02 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 14:58:04 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

sem_t	*creat_sem(char *name, int value)
{
	sem_t	*new_sem;

	new_sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (new_sem == SEM_FAILED)
	{
		sem_unlink(name);
		new_sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
		if (new_sem == SEM_FAILED)
			return (NULL);
	}
	return (new_sem);
}

int	init_phils(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->input_data[PHIL_NB])
	{
		data->phil_process[i].number = i + 1;
		data->phil_process[i].data = data;
		data->phil_process[i].last_eat = data->start;
		data->phil_process[i].eat_times = 0;
		data->phil_process[i].has_eaten = 0;
		data->phil_process[i].is_dead = 0;
		data->phil_process[i].name = ft_itoa(i + 1);
		data->phil_process[i].last_eating = creat_sem \
		(data->phil_process[i].name, 1);
		if (data->phil_process[i].last_eating == NULL \
		|| data->phil_process[i].name == NULL)
			exit(ft_putstr_error("phil data error\n"));
	}
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

int	initioizer(t_data *data, char **av, int ac)
{
	data->eat_all = 0;
	if (get_and_check_argv(data, av, ac) < 0)
		exit (-1);
	data->phil_process = (t_phil_process *)malloc(\
	sizeof(t_phil_process) * data->input_data[PHIL_NB]);
	if (!(data->phil_process))
		exit (ft_putstr_error("malloc error\n"));
	data->std_out = creat_sem(SEM_STDOUT, 1);
	data->forks = creat_sem(SEM_FORKS, data->input_data[PHIL_NB]);
	if (data->std_out == 0 || data->forks == 0)
		exit (ft_putstr_error("sem error\n"));
	return (init_phils(data));
}
