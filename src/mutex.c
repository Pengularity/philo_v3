/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:23:34 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/17 21:24:48 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	init_fork_mutexes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		if (pthread_mutex_init(&args->fork[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&args->fork[i]);
			free(args->fork);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_philo_mutexes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		if (pthread_mutex_init(&args->philo[i].last_meal_m, NULL) != 0
			|| pthread_mutex_init(&args->philo[i].times_eaten_m, NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&args->philo[i].last_meal_m);
				pthread_mutex_destroy(&args->philo[i].times_eaten_m);
			}
			return (false);
		}
		i++;
	}
	return (true);
}

bool	mutex_init(t_args *args)
{
	if (pthread_mutex_init(&args->print_m, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&args->is_dead_m, NULL) != 0)
	{
		pthread_mutex_destroy(&args->print_m);
		return (false);
	}
	if (pthread_mutex_init(&args->all_ate_required_times_m, NULL) != 0)
	{
		pthread_mutex_destroy(&args->print_m);
		pthread_mutex_destroy(&args->is_dead_m);
		return (false);
	}
	if (!init_fork_mutexes(args) || !init_philo_mutexes(args))
	{
		pthread_mutex_destroy(&args->print_m);
		pthread_mutex_destroy(&args->is_dead_m);
		pthread_mutex_destroy(&args->all_ate_required_times_m);
		return (false);
	}
	return (true);
}

void	destroy_mutexes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_destroy(&args->philo[i].times_eaten_m);
		pthread_mutex_destroy(&args->philo[i].last_meal_m);
		pthread_mutex_destroy(&args->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&args->all_ate_required_times_m);
	pthread_mutex_destroy(&args->is_dead_m);
	pthread_mutex_destroy(&args->print_m);
}
