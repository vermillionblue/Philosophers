/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:09 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 18:05:43 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to do:

// - create free functions and use destroy functions
// - calling process should check for deaths and meals 
// if meals_eaten = n_times_to_eat, program stops
//dont forget to destoy the mutexes at the end (frees resources): pthread_mutex_destroy(&mutex)

void	*routine_start(void* param)
{
	t_philo	phi;

	phi = *(t_philo *)param;
	if ((phi.philo_index) % 2 == 0)
		usleep(5000);
	while(1)
	{
		philo_eats(&phi);
		philo_sleeps(&phi);
		philo_thinks(&phi);
		// pthread_mutex_lock(phi.rules->exit_m);
		// if (phi.rules->exit == 1)
		// 	break ;
		// pthread_mutex_unlock(phi.rules->exit_m);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	data;

	check_input(argv, argc);
	data.start_time = get_time(0);
	enter_data(argv, &data);
	init_data(&data);
	init_threads(&data);
	//check functions
	//check_lastmeal(&data);
	join_threads(&data);
	/// free(all)
	return (1);
}