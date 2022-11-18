/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:41:06 by danisanc          #+#    #+#             */
/*   Updated: 2022/11/18 23:33:06 by danisanc         ###   ########.fr       */
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

typedef	struct s_rules t_rules;
/////utils
void		check_input(char **argv, int argc);
long int	ft_atol(const char *str);
int			ft_isdigit(int c);
void		enter_data(char **argv, t_rules *rules);
long		get_time(long start_time);

typedef struct	s_philo
{
	pthread_t		pt_id;
	int				philo_index; //non-zero index
	long			lastmeal;
	t_rules			*rules;
	int				meals_eaten;
	int				dead;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
}				t_philo;

typedef struct	s_rules
{
	int					n_philos;
	pthread_mutex_t		*forks;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					n_times_to_eat;
	int					exit;
	t_philo				*philos;
}				t_rules;
//// utils
void		print_time_n_index(t_philo *philo, char *str, char* colorcode);
//////////////// actions
void		philo_eats(t_philo *philo);
void		philo_sleephinks(t_philo *philo);
void		assign_forks(t_rules *data);
//////////// init.c
int			init_threads(t_rules *data);
void		join_threads(t_rules *data);
void		init_data(t_rules *data);
void		enter_data(char **argv, t_rules *rules);
////////// routine 
void		*routine_start(void *param);

#endif
