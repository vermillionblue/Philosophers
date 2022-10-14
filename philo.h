/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:06 by danisanc          #+#    #+#             */
/*   Updated: 2022/10/12 20:04:39 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"


typedef struct	s_rules t_rules;

typedef struct	s_philo
{
	int		philo_index; //non-zero index
	t_rules	*rules;
	int		dead;
}				t_philo;

typedef struct	s_rules
{
	int				n_philos;
	pthread_mutex_t	*forks;
	long			start_time;
	double			time_to_die;
	double			time_to_eat;
	double			time_to_sleep;
	int				n_times_to_eat;
	t_philo			*philos;
}				t_rules;

#endif
