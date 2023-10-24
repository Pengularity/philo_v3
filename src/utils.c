/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:19:26 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/24 15:46:08 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// bool	ft_atol(long *nb, char *nbr)
// {
// 	int		i;
// 	long	tmp;

// 	i = 0;
// 	*nb = 0;
// 	while (nbr[i])
// 	{
// 		tmp = *nb * 10 + (nbr[i] - 48);
// 		if (tmp < *nb)
// 			return (false);
// 		*nb = tmp;
// 		i++;
// 	}
// 	return (true);
// }

bool	ft_atoi(int *nb, char *nbr)
{
	int		i;
	int		tmp;

	i = 0;
	*nb = 0;
	while (nbr[i])
	{
		tmp = *nb * 10 + (nbr[i] - 48);
		if (tmp < *nb)
			return (false);
		*nb = tmp;
		i++;
	}
	return (true);
}

int	is_num(char *str)
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

void	ft_error(char *str)
{
	ft_putstr_fd(RED "Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET "\n", 2);
}
