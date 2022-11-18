/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:41 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 16:45:21 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// philo index 0 takes first and last fork, the rest take fork[index philo] and fork [index philo + 1] 
void	assign_forks(t_rules *data)
{
	int	i;

	i = 1;
	data->philos[0].right_f = data->forks[0];
	data->philos[0].left_f = data->forks[data->n_philos - 1];
	while (i < data->n_philos - 1)
	{
		data->philos[i].left_f = data->forks[i - 1];
		data->philos[i].right_f = data->forks[i];
		i++;
	}
}

void	update_lastmeal(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->start_time_m);
	pthread_mutex_lock(&philo->lastmeal_m);
	philo->lastmeal = get_time(philo->rules->start_time);
	pthread_mutex_unlock(&philo->lastmeal_m);
	pthread_mutex_unlock(&philo->rules->start_time_m);
	philo->meals_eaten++;
}

void philo_eats(t_philo *philo)
{
	/// takes forks and starts eating
	pthread_mutex_lock(&philo->left_f);
	print_time_n_index(philo, "has taken left fork", WHITE);
	pthread_mutex_lock(&philo->right_f);
	print_time_n_index(philo, "has taken right fork", WHITE);
	print_time_n_index(philo, "is eating", YELLOW);

	////// eats for time_to_eat milliseconds
	// pthread_mutex_lock(philo->rules->time_to_eat_m);
	// usleep(philo->rules->time_to_eat * 1000);
	// pthread_mutex_lock(philo->rules->time_to_eat_m);
	///////////// eats
	long long end;
	pthread_mutex_lock(&philo->rules->time_to_eat_m);
	end = get_time(0) + philo->rules->time_to_eat;
	while (get_time(0) < end)
		usleep(philo->rules->time_to_eat / 1000);
	pthread_mutex_unlock(&philo->rules->time_to_eat_m);
	//////////////////// stops eating and releases forks
	pthread_mutex_unlock(&philo->left_f);
	pthread_mutex_unlock(&philo->right_f);
	update_lastmeal(philo);
	//pthread_mutex_lock(philo->rules->n_times_to_eat_m);
	// printf("%d vs %d", philo->rules->n_times_to_eat, philo->meals_eaten);
	// print_time_n_index(philo, "has eaten x times", WHITE);
	//pthread_mutex_unlock(philo->rules->n_times_to_eat_m);
}

void	philo_thinks(t_philo *philo)
{
	print_time_n_index(philo, "is thinking", PURPLE);
}

void	philo_sleeps(t_philo *philo)
{
	long long end;

	print_time_n_index(philo, "is sleeping", BLUE);
	//////////////////////////
	pthread_mutex_lock(&philo->rules->time_to_sleep_m);
	end = get_time(0) + philo->rules->time_to_sleep;
	while (get_time(0) < end)
		usleep(philo->rules->time_to_sleep / 1000);
	pthread_mutex_unlock(&philo->rules->time_to_sleep_m);

}