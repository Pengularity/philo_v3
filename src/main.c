/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:33:19 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/18 13:24:30 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	run_simulation(t_args *args)
{
	int	i;

	i = 0;
	args->start_time = current_time();
	while (i < args->num_philo)
	{
		args->philo[i].last_meal = current_time();
		if (pthread_create(&args->philo[i].thread_id, NULL,
				(void *)philo_routine, &args->philo[i]))
		{
			while (i > 0)
			{
				i--;
				pthread_join(args->philo[i].thread_id, NULL);
			}
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
		return (ft_error("Invalid number of arguments"), 1);
	if (!parse_args(ac, av, &args))
		return (ft_error("Invalid arguments"), 1);
	if (!args_init(&args))
		return (ft_error("Failed to initialize structures"), 1);
	if (!mutex_init(&args))
		return (ft_error("Failed to initialize mutexes"), 1);
	philo_init(&args);
	if (!run_simulation(&args))
	{
		ft_error("simulation init failed");
		destroy_mutexes(&args);
		return (1);
	}
	monitor_status(&args);
	destroy_mutexes(&args);
	free_args(&args);
}
