/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:51:00 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/19 20:59:35 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_numeric_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_num(av[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	set_values(t_args *args, char **av, int ac)
{
	if (!ft_atoi(&args->num_philo, av[1]))
		return (false);
	if (!ft_atoi(&args->time_to_die, av[2]))
		return (false);
	if (!ft_atoi(&args->time_to_eat, av[3]))
		return (false);
	if (!ft_atoi(&args->time_to_sleep, av[4]))
		return (false);
	if (ac == 6)
	{
		if (!ft_atoi(&args->num_must_eat, av[5]) || args->num_must_eat <= 0)
			return (false);
	}
	else
		args->num_must_eat = -1;
	return (true);
}

bool	parse_args(int ac, char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
		return (false);
	if (!check_numeric_args(av))
		return (false);
	if (!set_values(args, av, ac))
		return (false);
	if (args->num_philo <= 0 || args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0)
		return (false);
	args->is_dead = -1;
	args->all_ate_required_times = -1;
	return (true);
}

void	philo_init(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		(args->philo)[i].id = i + 1;
		(args->philo)[i].times_eaten = 0;
		(args->philo)[i].last_meal = 0;
		(args->philo)[i].left_fork = &args->fork[i];
		(args->philo)[i].right_fork = &args->fork[(i + 1) % args->num_philo];
		(args->philo)[i].args = args;
		i++;
	}
}

bool	args_init(t_args *args)
{
	args->philo = malloc(sizeof(t_philo) * args->num_philo);
	if (!args->philo)
		return (false);
	args->fork = malloc(sizeof(pthread_mutex_t) * args->num_philo);
	if (!args->fork)
	{
		free(args->philo);
		return (false);
	}
	return (true);
}
