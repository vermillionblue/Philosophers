/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:41 by danisanc          #+#    #+#             */
/*   Updated: 2022/10/16 22:06:33 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//assuming left and right fork can be taken from anywhere on the table
void philo_eats(t_philo *phi, t_rules *rules)
{
	int i;

	i = 0;
	while(i < rules->n_philos)
	{
		if (pthread_mutex_lock(&rules->forks[i]) == 0)
		{
			printf("grabbed left fork");
			phi->left_f = 1;
			while(i < rules->n_philos)
			{
				if (pthread_mutex_lock(&rules->forks[i]) == 0)
				{
					printf("grabbed right fork");
					phi->right_f = 1;
				}
				i++;
			}
		}
		i++;
	}
	if (phi->left_f && phi->right_f)
	{
		printf(PURPLE);
		printf("--- %d is eating\n", phi->philo_index);
		printf(WHITE);
	}
}	