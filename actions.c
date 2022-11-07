/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:41 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/07 09:42:38 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// philo index 0 takes first and last fork, the rest take fork[index philo] and fork [index philo + 1] 
void	assign_forks(t_rules *data)
{
	int	i;

	i = 1;
	data->philos[0].right_f = &data->forks[0];
	data->philos[0].left_f = &data->forks[data->n_philos - 1];
	while (i < data->n_philos - 1)
	{
		data->philos[i].left_f = &data->forks[i - 1];
		data->philos[i].right_f = &data->forks[i];
		i++;
	}
}

void	update_lastmeal(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(rules->start_time_m);
	philo->lastmeal = get_time(rules->start_time);
	pthread_mutex_unlock(rules->start_time_m);
	philo->meals_eaten++;
}

void philo_eats(t_philo *philo, t_rules *rules)
{
	//print has taken left/right fork
	pthread_mutex_lock(philo->left_f);
	pthread_mutex_lock(philo->right_f);
	print_time_n_index(philo);
	printf(YELLOW);
	printf("eating\n");
	printf(WHITE);
	pthread_mutex_lock(rules->time_to_eat_m);
	usleep(rules->time_to_eat * 1000);
	pthread_mutex_unlock(rules->time_to_eat_m);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	update_lastmeal(philo, rules);
}

void	philo_thinks(t_philo *philo)
{
	print_time_n_index(philo);
	printf(PURPLE);
	printf("thinking\n");
	printf(WHITE);
}

void	philo_sleeps(t_philo *philo)
{
	print_time_n_index(philo);
	printf(BLUE);
	printf("thinking\n");
	printf(WHITE);
	pthread_mutex_lock(philo->rules->time_to_sleep_m);
	usleep(philo->rules->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->rules->time_to_sleep_m);
}