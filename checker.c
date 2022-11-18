/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:25:07 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 16:47:25 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_lastmeal(t_rules *data)
{
	int	i;

	while(1)
	{
		i = 0;
		while(i < data->n_philos)
		{
			pthread_mutex_lock(&data->philos[i].lastmeal_m);
			if (data->philos[i].lastmeal >= data->time_to_die)
			{
				//pthread_mutex_lock(data->exit_m);
				//data->exit = 1;
				printf("stop\n");
				//pthread_mutex_unlock(data->exit_m);
			}
			pthread_mutex_unlock(&data->philos[i].lastmeal_m);
			pthread_mutex_lock(&data->philos[i].meals_eaten_m);
			printf("%d vs %d\n", data->philos[i].meals_eaten, data->n_times_to_eat);
			if (data->philos[i].meals_eaten >= data->n_times_to_eat)
			{
				//pthread_mutex_lock(philo->rules->exit_m);
				//philo->rules->exit = 1;
				exit(1);
				//pthread_mutex_unlock(philo->rules->exit_m);
			}
			pthread_mutex_unlock(&data->philos[i].meals_eaten_m);
			i++;
		}
	}
}