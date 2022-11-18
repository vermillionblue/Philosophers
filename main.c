/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:09 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 23:30:41 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to do:

// - create free functions and use destroy functions
//dont forget to destoy the mutexes at the end (frees resources): pthread_mutex_destroy(&mutex)

// void	destroy(t_rules *data)
// {
	
// }

/// checks that every philo has at least eaten the n_times_to_eat and turn on the flag
// 
void	meal_checker(t_rules *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (data->philos[i].lastmeal > data->time_to_die)
			{
				print_time_n_index(&data->philos[i], "has died", RED);
				data->exit = 1;
				return ;
			}
			if (data->philos[i].meals_eaten >= data->n_times_to_eat
				&& data->n_times_to_eat != -1)
			{
				data->exit = 1;
				return ;
			}
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
	meal_checker(&data);
	join_threads(&data);
	/// free(all)
	return (1);
}
