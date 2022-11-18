/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:25:07 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 21:55:01 by danisanc         ###   ########.fr       */
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
			//usleep(5000);
			if (data->philos[i].lastmeal > data->time_to_die)
			{
				data->exit = 1;
				print_time_n_index(&data->philos[i], "has died", RED);
				return ;
			}
			if (data->philos[i].meals_eaten >= data->n_times_to_eat)
			{
				data->exit = 1;
				printf("all meals eaten\n");
				return ;
			}
			i++;
		}
	}
}