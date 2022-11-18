/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:06 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/12 22:26:16 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define RED "\033[0;31m"		//for dying D:
# define GREEN "\033[0;32m"	
# define YELLOW "\033[0;33m"	// for eating 
# define BLUE "\033[0;34m"    //for sleeping
# define PURPLE "\033[0;35m"	//for thinking
# define CYAN "\033[0;36m"		//for time
# define WHITE "\033[0;37m"

typedef struct	s_rules t_rules;

/////utils
void		check_input(char **argv, int argc);
long int	ft_atol(const char *str);
int			ft_isdigit(int c);
void		enter_data(char **argv, t_rules *rules);
long long		get_time(long long start_time);

typedef struct	s_philo
{
	pthread_t		pt_id;
	int				philo_index; //non-zero index
	long long		lastmeal;
	pthread_mutex_t	*lastmeal_m;
	t_rules			*rules;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_m;
	int				dead;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
}				t_philo;

typedef struct	s_rules
{
	int					n_philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*start_time_m;
	long long			start_time;
	pthread_mutex_t		*time_to_die_m;
	int					time_to_die;
	pthread_mutex_t		*time_to_eat_m;
	int					time_to_eat;
	pthread_mutex_t		*time_to_sleep_m;
	int					time_to_sleep;
	pthread_mutex_t		*n_times_to_eat_m;
	int					n_times_to_eat;
	int					exit;
	pthread_mutex_t		*exit_m;
	t_philo				*philos;
}				t_rules;
//// utils
void	print_time_n_index(t_philo *philo, char* str, char* colorcode);
//////////////// actions
void	philo_eats(t_philo *philo);
void	philo_thinks(t_philo *philo);
void	philo_sleeps(t_philo *philo);
void	assign_forks(t_rules *data);
//////////// init.c
void	init_mutexes(t_rules *data);
int		init_threads(t_rules *data);
void	join_threads(t_rules *data);
void	init_data(t_rules *data);
void	enter_data(char **argv, t_rules *rules);
////////// routine 
void	*routine_start(void* param);
/////////// check.c
void	check_lastmeal(t_rules *data);


#endif
