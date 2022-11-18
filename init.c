/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:45:52 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/12 22:26:34 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_rules *data)
{
	data->start_time_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->start_time_m, NULL);
	data->time_to_die_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_to_die_m, NULL);
	data->time_to_eat_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_to_eat_m, NULL);
	data->time_to_sleep_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_to_sleep_m, NULL);
	data->n_times_to_eat_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->n_times_to_eat_m, NULL);
	data->exit_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->exit_m , NULL);
}

void	enter_data(char **argv, t_rules *rules)
{
	rules->n_philos = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	rules->exit = 0;
	if (argv[5])
		rules->n_times_to_eat = ft_atol(argv[5]);
}

void	init_data(t_rules *data)
{
	int	i;

	i = 0;
	data->start_time = get_time(0);
	data->philos = malloc(sizeof(t_philo) * (data->n_philos));
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philos));
	while (i < data->n_philos)
	{
		data->philos[i].lastmeal_m = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->philos[i].lastmeal_m, NULL);
		pthread_mutex_init(&data->philos[i].meals_eaten_m, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].rules = data;
		data->philos[i].philo_index = i + 1;
		data->philos[i].dead = 0; //false
		data->philos[i].meals_eaten = 0;
		data->philos[i].lastmeal = data->start_time;
		i++;
	}
	assign_forks(data);
	init_mutexes(data);
}

int	init_threads(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].pt_id, NULL, &routine_start, (void *)&data->philos[i]) != 0)
		{
			perror("pthread create error\n");
			exit (EXIT_FAILURE);
		}	
		i++;
	}
	return (0);
}

void join_threads(t_rules *data)
{
	int	i;

	i = 0;
	while (i <  data->n_philos)
	{
		if (pthread_join(data->philos[i].pt_id, NULL) != 0)
		{
			perror("pthread join error\n");
			exit (EXIT_FAILURE);
		}
		i++;
	}
}