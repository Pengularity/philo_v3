/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:19:26 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/17 21:02:11 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_atol(long *nb, char *nbr)
{
	int		i;
	long	tmp;

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

void	free_args(t_args *args)
{
	free(args->philo);
	free(args->fork);
}

