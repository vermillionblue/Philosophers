/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:11:18 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/19 18:44:19 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((((time.tv_sec * 1000L) + (time.tv_usec / 1000L))) - start_time));
}

void	print_time_n_index(t_philo *philo, char *str, char *colorcode)
{
	pthread_mutex_lock(&philo->rules->exit_m);
	if (philo->rules->exit == 1)
	{
		pthread_mutex_unlock(&philo->rules->exit_m);
		usleep(100000000);
	}
	pthread_mutex_unlock(&philo->rules->exit_m);
	pthread_mutex_lock(&philo->rules->print_m);
	printf("%s%ld ms %s", CYAN, get_time(philo->rules->start_time), WHITE);
	printf("%d %s%s%s\n", philo->philo_index + 1, colorcode, str, WHITE);
	pthread_mutex_unlock(&philo->rules->print_m);
}
