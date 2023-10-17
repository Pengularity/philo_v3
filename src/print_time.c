/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:25:54 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/17 21:02:42 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	print_status(t_philo *philo, char *color, char *status)
{
	long	time;
	int		ret;

	time = current_time() - philo->args->start_time;
	pthread_mutex_lock(&philo->args->print_m);
	ret = printf("%ld %d %s%s%s\n", time, philo->id, color, status, RESET);
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

void	ft_sleep(long time_in_ms)
{
	long	start_time;
	long	elapsed_time;

	start_time = current_time();
	elapsed_time = 0;
	while (elapsed_time < time_in_ms)
	{
		if (time_in_ms - elapsed_time > 100)
			usleep(10 * 1000);
		else
			usleep((time_in_ms - elapsed_time) * 1000);
		elapsed_time = current_time() - start_time;
	}
}

static void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (fd >= 0)
	{
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

int	ft_error(char *str)
{
	ft_putstr_fd(RED "Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET "\n", 2);
	return (0);
}
