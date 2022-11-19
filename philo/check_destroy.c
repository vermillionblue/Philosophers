/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:25:31 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/19 22:21:44 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_rules *data)
{
	int	i;

	i = 0;
	free(data->philos);
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->exit_m);
	free(data->forks);
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	detach_all(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_detach(data->philos[i].pt_id);
		pthread_mutex_destroy(&data->philos[i].meals_eaten_m);
		pthread_mutex_destroy(&data->philos[i].lastmeal_m);
		i++;
	}
}

int	check_meals_eaten(t_rules *data, int i, int *philos_done)
{
	pthread_mutex_lock(&data->philos[i].meals_eaten_m);
	if (data->philos[i].meals_eaten >= data->n_times_to_eat
		&& data->philos[i].eaten_all_meals == 0
		&& data->n_times_to_eat != -1)
	{
		*philos_done = *philos_done + 1;
		data->philos[i].eaten_all_meals = 1;
		if (*philos_done == data->n_philos)
		{
			pthread_mutex_lock(&data->exit_m);
			data->exit = 1;
			pthread_mutex_unlock(&data->exit_m);
			usleep(100000 * data->n_philos);
			detach_all(data);
			return (1);
		}
	}
	pthread_mutex_unlock(&data->philos[i].meals_eaten_m);
	return (0);
}

int	check_lastmeal(t_rules *data, int i)
{
	pthread_mutex_lock(&data->philos[i].lastmeal_m);
	if (get_time(data->start_time)
		- data->philos[i].lastmeal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philos[i].lastmeal_m);
		print_time_n_index(&data->philos[i], "has died", RED);
		pthread_mutex_lock(&data->exit_m);
		data->exit = 1;
		pthread_mutex_unlock(&data->exit_m);
		usleep(100000 * data->n_philos);
		detach_all(data);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].lastmeal_m);
	return (0);
}

void	main_checker(t_rules *data)
{
	int	i;
	int	philos_done;

	philos_done = 0;
	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (check_lastmeal(data, i) == 1)
				return ;
			if (check_meals_eaten(data, i, &philos_done) == 1)
				return ;
			i++;
		}
	}
}
