/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:11:18 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 23:16:31 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
// tv_sec : It is the number of seconds since the epoch.
// tv_usec :It is additional microseconds after number of seconds calculation since the epoch

long	get_time(long start_time)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return(((((time.tv_sec * 1000L) + (time.tv_usec / 1000L))) - start_time));
}

void	print_time_n_index(t_philo *philo, char* str, char* colorcode)
{
	//usleep(); maybe needed
	usleep(200);
	if (philo->rules->exit == 1)
			return ;
	printf("%s%ld ms %s", CYAN, get_time(philo->rules->start_time), WHITE);
	printf("%d %s%s%s\n", philo->philo_index, colorcode, str, WHITE);
	philo->meals_eaten++;
}