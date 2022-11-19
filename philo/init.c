/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:45:52 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/19 18:10:56 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	enter_data(char **argv, t_rules *rules)
{
	rules->n_philos = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	rules->exit = 0;
	if (argv[5])
		rules->n_times_to_eat = ft_atol(argv[5]);
	else
		rules->n_times_to_eat = -1;
}

void	init_data(t_rules *data)
{
	int	i;

	i = 0;
	data->start_time = get_time(0);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philos));
	data->philos = malloc(data->n_philos * sizeof(t_philo));
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->exit_m, NULL);
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].lastmeal_m, NULL);
		pthread_mutex_init(&data->philos[i].meals_eaten_m, NULL);
		data->philos[i].rules = data;
		data->philos[i].philo_index = i;
		data->philos[i].dead = 0;
		data->philos[i].lastmeal = 0;
		data->philos[i].meals_eaten = 0;
		i++;
	}
	assign_forks(data);
}

int	init_threads(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].pt_id, NULL, &routine_start, \
		(void *)&data->philos[i]) != 0)
		{
			perror("pthread create error\n");
			exit (EXIT_FAILURE);
		}	
		i++;
	}
	return (0);
}
