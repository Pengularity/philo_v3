/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:46:09 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/16 02:56:56 by wnguyen          ###   ########.fr       */
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

# define WHITE "\033[97m"
# define RED "\033[91m"
# define GREEN "\033[92m"
# define BLUE "\033[94m"
# define YELLOW "\033[93m"
# define BRIGHT_GREEN "\033[92m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal;
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
	int				num_satiated;
	pthread_mutex_t	is_dead_m;		
	pthread_mutex_t	num_satiated_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}		t_args;


bool		print_status(t_philo *philo, char *color, char *status);
int			ft_error(char *str);
long int	current_time(void);

/*routine*/

void		*philo_routine(void *void_philo);

#endif