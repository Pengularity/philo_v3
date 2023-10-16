/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:33:19 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/16 01:49:08 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i > 0);
}

bool	parse_args(int ac, char **av, t_args *args)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_num(av[i]))
			return (0);
		i++;
	}
	args->num_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->num_must_eat = -1;
	if (ac == 6)
		args->num_must_eat = ft_atoi(av[5]);
	if (args->num_philo <= 0 || args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0 || (ac == 6 && args->num_must_eat <= 0))
		return (false);
	return (true);
}

static void	philo_init(t_args *args)
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
		i++;
	}
}

int	main(int ac, char **av)
{
	t_args	args;

	if (av < 5 || av > 6)
		return (ft_error("Invalid number of arguments"), 1);
	if (!parse_args(ac, av, &args))
		return (ft_error("Invalid arguments"), 1);
	philo_init(&args);
	if (!mutex_init(&args))
		return (ft_error("Mutex init failed"), cleanup(&args), 1);
	if (!run_simulation(&args))
		return (ft_error("simulation init failed"), full_cleanup(&args), 1);
	monitor_health(&args);
	full_cleanup(&args);
}
