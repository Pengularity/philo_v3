/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:25:54 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/19 20:23:49 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

bool	print_status(t_philo *philo, char *color, char *status)
{
	long	time;
	int		ret;

	time = current_time() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_m);
	pthread_mutex_lock(&philo->args->is_dead_m);
	if (philo->args->is_dead > 0 && !strcmp(status, "died") == 0)
		return (pthread_mutex_unlock(&philo->args->is_dead_m),
			pthread_mutex_unlock(&philo->args->print_m), false);
	ret = printf("%ld %d %s%s%s\n", time, philo->id, color, status, RESET);
	pthread_mutex_unlock(&philo->args->is_dead_m);
	pthread_mutex_unlock(&philo->args->print_m);
	return (ret >= 0);
}

long int	current_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

bool	ft_sleep(t_args *args, int time_duration)
{
	long	start_time;
	long	elapsed_time;
	long	time;

	time = args->start_time;
	start_time = current_time();
	elapsed_time = time - time;
	while (elapsed_time < time_duration)
	{
		if (time_duration - elapsed_time > 100)
			usleep(5 * 1000);
		else
			usleep((time_duration - elapsed_time) * 1000);
		elapsed_time = current_time() - start_time;
	}
	return (false);
}

// bool	ft_sleep(t_args *args, int time_duration)
// {
// 	int	time;

// 	time = current_time() - args->start_time;
// 	while ((current_time() - args->start_time)
// 		- time < time_duration)
// 	{
// // 		pthread_mutex_lock(&args->all_ate_required_times_m);
// // 		pthread_mutex_lock(&args->is_dead_m);
// // 		if (args->is_dead == 1 || args->all_ate_required_times == 1)
// // 		{
// // 			pthread_mutex_unlock(&args->all_ate_required_times_m);
// // 			pthread_mutex_unlock(&args->is_dead_m);
// // 			return (true);
// // 		}
// // 		pthread_mutex_unlock(&args->all_ate_required_times_m);
// // 		pthread_mutex_unlock(&args->is_dead_m);
// 		usleep(500);
// 	}
// 	return (false);
// }

void	free_args(t_args *args)
{
	if (args->all_ate_required_times == 1)
		printf(GREEN "Each philo ate %d times\n" RESET, args->num_must_eat);
	free(args->philo);
	free(args->fork);
}
