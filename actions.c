/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:41 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/19 15:24:45 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_start(void *param)
{
	t_philo	*phi;

	phi = (t_philo *)param;
	if ((phi->philo_index) % 2 == 0)
		usleep(2000);
	while (1)
	{
		philo_eats(phi);
		philo_sleephinks(phi);
	}
	return (NULL);
}

// philo index 0 takes first and last fork, 
//the rest take fork[index philo] and fork [index philo + 1] 
void	assign_forks(t_rules *data)
{
	int	i;

	i = 1;
	data->philos[0].right_f = &data->forks[0];
	data->philos[0].left_f = &data->forks[data->n_philos - 1];
	while (i < data->n_philos)
	{
		data->philos[i].left_f = &data->forks[i - 1];
		data->philos[i].right_f = &data->forks[i];
		i++;
	}
}

static void	waiting4it(long time2blab)
{
	long	end;

	end = get_time(0) + time2blab;
	while (get_time(0) < end)
		usleep(time2blab / 1000);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_time_n_index(philo, "has taken left fork", WHITE);
	pthread_mutex_lock(philo->right_f);
	print_time_n_index(philo, "has taken right fork", WHITE);
	pthread_mutex_lock(&philo->lastmeal_m);
	philo->lastmeal = get_time(philo->rules->start_time);
	pthread_mutex_unlock(&philo->lastmeal_m);
	print_time_n_index(philo, "is eating", YELLOW);
	waiting4it(philo->rules->time_to_eat);
	pthread_mutex_lock(&philo->meals_eaten_m);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_m);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	philo_sleephinks(t_philo *philo)
{
	print_time_n_index(philo, "is sleeping", BLUE);
	waiting4it(philo->rules->time_to_sleep);
	print_time_n_index(philo, "is thinking", PURPLE);
}
