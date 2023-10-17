/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:46:48 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/17 21:41:11 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	is_dead(t_philo *philo)
{
	long	time;

	if (!philo)
	{
		printf("philo structure not initialized");
		return (false);
	}

	time = current_time();
	pthread_mutex_lock(&philo->last_meal_m);
	if (time - philo->last_meal >= philo->args->time_to_die)
		return (pthread_mutex_unlock(&philo->last_meal_m), true);
	pthread_mutex_unlock(&philo->last_meal_m);
	return (false);
}

static inline bool	check_death(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		if (is_dead(&args->philo[i]))
		{
			pthread_mutex_lock(&args->is_dead_m);
			args->is_dead = 1;
			pthread_mutex_unlock(&args->is_dead_m);
			print_status(&args->philo[i], RED, "died");
			return (true);
		}
		i++;
	}
	return (false);
}

static inline bool	ate_enough(t_args *args)
{
	int	i;

	if (args->num_must_eat >= 0)
	{
		i = 0;
		while (i < args->num_philo)
		{
			pthread_mutex_lock(&args->philo[i].times_eaten_m);
			if (args->philo[i].times_eaten < args->num_must_eat)
			{
				pthread_mutex_unlock(&args->philo[i].times_eaten_m);
				break ;
			}
			pthread_mutex_unlock(&args->philo[i].times_eaten_m);
			i++;
		}
		if (i == args->num_philo)
		{
			pthread_mutex_lock(&args->all_ate_required_times_m);
			args->all_ate_required_times = 1;
			pthread_mutex_unlock(&args->all_ate_required_times_m);
		}
		return (true);
	}
	return (false);
}

void	monitor_status(t_args *args)
{
	int	i;
	
	usleep(500);
	while (!check_death(args) && !ate_enough(args))
		ft_sleep(500);
	i = 0;
	while (i < args->num_philo)
	{
		pthread_join(args->philo[i].thread_id, NULL);
		i++;
	}
}
