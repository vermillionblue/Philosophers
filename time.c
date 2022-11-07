/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:11:18 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/07 09:40:25 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
// tv_sec : It is the number of seconds since the epoch.
// tv_usec :It is additional microseconds after number of seconds calculation since the epoch

time_t	get_time(time_t start_time)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return((((time.tv_sec * 1000) + (time.tv_usec / 1000))) - start_time);
}
