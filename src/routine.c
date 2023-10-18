/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:49:59 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/18 16:43:15 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	pickup_forks(t_philo *philo)
{
	if (philo->id & 1)
	{
		pthread_mutex_lock(philo->left_fork);
		// if (!print_status(philo, WHITE, "has taken a fork"))
		// 	return (pthread_mutex_unlock(philo->left_fork), false);
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, WHITE, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), false);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		// if (!print_status(philo, WHITE, "has taken a fork"))
		// 	return (pthread_mutex_unlock(philo->right_fork), false);
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, WHITE, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), false);
	}
	return (true);
}

static inline bool	eat(t_philo *philo)
{
	if (!pickup_forks(philo))
		return (false);
	if (!print_status(philo, GREEN, "is eating"))
		return ((pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), (false)));
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->last_meal_m);
	ft_sleep(philo->args->time_to_eat);
	pthread_mutex_lock(&philo->times_eaten_m);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_m);
	if (philo->id & 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (true);
}

static inline bool	sleep_and_think(t_philo *philo)
{
	int	intervals;
	int	interval_duration;
	int	i;

	intervals = 50;
	interval_duration = (philo->args->time_to_sleep * 1000) / intervals;
	i = 0;
	if (!print_status(philo, BLUE, "is sleeping"))
		return (false);
	while (i < intervals)
	{
		usleep(interval_duration);
		pthread_mutex_lock(&philo->args->is_dead_m);
		if (philo->args->is_dead == 1)
			return (pthread_mutex_unlock(&philo->args->is_dead_m), false);
		pthread_mutex_unlock(&philo->args->is_dead_m);
		i++;
	}
	// ft_sleep(philo->args->time_to_sleep);
	if (!print_status(philo, YELLOW, "is thinking"))
		return (false);
	return (true);
}

bool	check_flag(t_args *args)
{
	pthread_mutex_lock(&args->is_dead_m);
	if (args->is_dead >= 0)
		return (pthread_mutex_unlock(&args->is_dead_m), true);
	pthread_mutex_unlock(&args->is_dead_m);
	pthread_mutex_lock(&args->all_ate_required_times_m);
	if (args->all_ate_required_times >= 0)
		return (pthread_mutex_unlock(&args->all_ate_required_times_m), true);
	pthread_mutex_unlock(&args->all_ate_required_times_m);
	return (false);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->args->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, WHITE, "has taken a fork");
		while (check_flag(philo->args))
			ft_sleep(125);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (!check_flag(philo->args))
	{
		if (!(philo->id & 1))
			usleep(500);
		if (!eat(philo))
			break ;
		if (!sleep_and_think(philo))
			break ;
		usleep((philo->args->time_to_eat > philo->args->time_to_sleep)
			* (philo->args->time_to_eat - philo->args->time_to_sleep) + 25);
	}
	return (NULL);
}
