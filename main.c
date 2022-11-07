/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:09 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/07 09:47:12 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to do:

// - create free functions and use destroy functions
// - calling process should check for deaths and meals 
//- print "has taken fork"
// if meals_eaten = n_times_to_eat, program stops
//dont forget to destoy the mutexes at the end (frees resources): pthread_mutex_destroy(&mutex)

void	*routine_start(void* param)
{
	t_philo	phi;

	phi = *(t_philo *)param;
	philo_eats(&phi, phi.rules);
	philo_sleeps(&phi);
	philo_thinks(&phi);
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
	/// free(all)
	return (1);
}