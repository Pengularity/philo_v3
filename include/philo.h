/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:46:09 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/18 17:16:21 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

# define WHITE "\033[97m"
# define RED "\033[91m"
# define GREEN "\033[92m"
# define BLUE "\033[94m"
# define YELLOW "\033[93m"
# define GREY "\033[90m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	times_eaten_m;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_args	*args;
}		t_philo;

typedef struct s_args
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_must_eat;
	int				is_dead;
	int				all_ate_required_times;
	pthread_mutex_t	is_dead_m;		
	pthread_mutex_t	all_ate_required_times_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}		t_args;

/* utils */

bool		ft_atol(long *nb, char *nbr);
bool		ft_atoi(int *nb, char *nbr);
int			is_num(char *str);
void		free_args(t_args *args);

/* print_time */

int			ft_error(char *str);
bool		print_status(t_philo *philo, char *color, char *status);
long int	current_time(void);
void		ft_sleep(long time_in_ms);

/* parse_init */

bool		parse_args(int ac, char **av, t_args *args);
void		philo_init(t_args *args);
bool		args_init(t_args *args);

/*routine*/

void		*philo_routine(t_philo *philo);
bool		check_flag(t_args *args);

/* mutex */

bool		mutex_init(t_args *args);
void		destroy_mutexes(t_args *args);

/* monitor */

void		monitor_status(t_args *args);

#endif