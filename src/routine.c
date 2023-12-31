/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:49:59 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/24 15:40:42 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, GREY, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), false);
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, GREY, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), false);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, GREY, "has taken a fork"))
			return (pthread_mutex_unlock(philo->right_fork), false);
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, GREY, "has taken a fork"))
			return (pthread_mutex_unlock(philo->right_fork),
				pthread_mutex_unlock(philo->left_fork), false);
	}
	return (true);
}

static inline bool	eat(t_philo *philo)
{
	if (!pickup_forks(philo))
		return (false);
	if (!print_status(philo, RED, "is eating"))
		return ((pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), (false)));
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->last_meal_m);
	ft_sleep(philo->args, philo->args->time_to_eat);
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
	if (!print_status(philo, BLUE, "is sleeping"))
		return (false);
	ft_sleep(philo->args, philo->args->time_to_sleep);
	if (!print_status(philo, GREEN, "is thinking"))
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
	if (!print_status(philo, GREEN, "is thinking"))
		return (false);
	if (philo->args->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, GREY, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		usleep(philo->args->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		ft_sleep(philo->args, philo->args->time_to_eat);
	while (!check_flag(philo->args))
	{
		if (!eat(philo) || check_flag(philo->args))
			break ;
		if (!sleep_and_think(philo) || check_flag(philo->args))
			break ;
		ft_sleep(philo->args,
			((philo->args->time_to_eat > philo->args->time_to_sleep)
				* (philo->args->time_to_eat
					- philo->args->time_to_sleep) + 5));
	}
	return (NULL);
}
