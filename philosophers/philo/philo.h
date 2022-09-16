/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:01:34 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:48 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define PHIL_NB 0
# define DIE_TIME 1
# define EAT_TIME 2
# define SLEEP_TIME 3
# define EAT_TIMES 4

typedef struct s_phil_thread
{
	int				number;
	pthread_t		thread;

	void			*data;
	void			*left_fork;
	void			*right_fork;

	int				eat_times;
	unsigned long	last_eat;
}	t_phil_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct s_data
{
	int				is_dead;
	t_mutex			is_dead_cheack;
	int				eat_all;

	unsigned long	start;

	int				input_data[6];
	t_phil_thread	*phil_threads;
	t_mutex			*forks;
	t_mutex			std_out;
	t_mutex			last_eating;
	t_mutex			eat_times_check;

}	t_data;
void			ft_putstr(char *s);
int				ft_putstr_error(char *s);
int				initioizer(t_data *data, char **av, int ac);
void			*act(void *args);
int				print_act(char *s, t_phil_thread *pthread, int isdead);
void			print_unsigned_number(unsigned long int num, int base, char x);
unsigned long	gettime_to_mls(void);
void			clean_all_malloc(t_data *data);
void			clean_all(t_data *data);
int				is_dead_cheack(t_data *data);
int				init_mutex(t_data *data);
int				dead_and_eat_all_checker(t_data *data);
#endif