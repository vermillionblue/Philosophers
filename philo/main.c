/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:09 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/19 18:15:01 by danisanc         ###   ########.fr       */
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

// void	check_meals_eaten()
// {
// 	pthread_mutex_lock(&data->exit_m);
// 				data->exit = 1;
// 				pthread_mutex_unlock(&data->exit_m);
// 				usleep(100000 * data->n_philos);
// 				detach_all(data);
// }

// void	check_lastmeal()
// {
// 	print_time_n_index(&data->philos[i], "has died", RED);
// 				pthread_mutex_lock(&data->exit_m);
// 				data->exit = 1;
// 				pthread_mutex_unlock(&data->exit_m);
// 				usleep(20000000);
// 				detach_all(data);
// }







void	main_checker(t_rules *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&data->philos[i].lastmeal_m);
			if (get_time(data->start_time) - data->philos[i].lastmeal > data->time_to_die)
			{
				//check_lastmeal()
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].lastmeal_m);
			pthread_mutex_lock(&data->philos[i].meals_eaten_m);
			if (data->philos[i].meals_eaten >= data->n_times_to_eat
				&& data->n_times_to_eat != -1)
			{
				//check_meals_eaten()
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].meals_eaten_m);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_rules	data;

	check_input(argv, argc);
	data.start_time = get_time(0);
	enter_data(argv, &data);
	init_data(&data);
	init_threads(&data);
	main_checker(&data);
	destroy(&data);
	return (1);
}
