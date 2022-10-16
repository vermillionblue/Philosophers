/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:09 by danisanc          #+#    #+#             */
/*   Updated: 2022/10/16 22:04:08 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//dont forget to destoy the mutexes at the end (frees resources): pthread_mutex_destroy(&mutex)

void	*routine_start(void* param)
{
	t_philo	phi;
	struct	timeval time;
	long long	current_time;

	phi = *(t_philo *)param;
	gettimeofday(&time, NULL);
	current_time = (time.tv_usec - phi.rules->start_time) / 1000LL;
	printf(CYAN);
	printf("%lld ", current_time);
	printf(WHITE);
	printf("xx");
	philo_eats(&phi, phi.rules);
	return (NULL);
}

void	init_data(t_rules *data, char **argv)
{
	int	i;
	(void)argv;

	i = 0;
	//data->start_time = 1;
	data->time_to_die = 1;
	data->time_to_eat = 1;
	data->time_to_sleep = 1;
	data->n_times_to_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].left_f = 0;
		data->philos[i].right_f = 0;
		data->philos[i].rules = data;
		data->philos[i].philo_index = i + 1;
		data->philos[i].dead = 0;

		i++;
	}
}

int	init_threads(t_rules *data)
{
	pthread_t ph[data->n_philos - 1];
	int	i;
	

	i = 0;
	while (i < data->n_philos)
	{
		//data->philo_name = i;
		if (pthread_create(&ph[i], NULL, &routine_start, (void *)&data->philos[i]) != 0)
		{
			perror("pthread create error\n");
			exit (EXIT_FAILURE);
		}	
		i++;
	}
	i = 0;
	while (i <  data->n_philos)
	{
		if (pthread_join(ph[i], NULL) != 0)
		{
			perror("pthread create error\n");
			exit (EXIT_FAILURE);
		}
		printf("%d finished\n", i);
		i++;
	}
	return (0);
}

// int	check_info()
// {
	
// }

int	main(int argc, char **argv)
{
	struct	timeval time;
	//long	time_in_mill;
	t_rules	data;
	// int		start;

	// start = 0;
	(void)argv;
	(void)argc;
	gettimeofday(&time, NULL);
	data.start_time = time.tv_usec;
	data.n_philos = 4;
	init_data(&data, argv);
	init_threads(&data);
	return (1);
}