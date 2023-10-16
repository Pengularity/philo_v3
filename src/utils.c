/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 01:19:26 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/16 01:23:11 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_atol(long *nb, char *nbr)
{
	int	i;

	i = 0;
	*nb = 0;
	while (nbr[i])
	{
		if (*nb > *nb * 10 + nbr[i] + 48)
			return (false);
		*nb *= 10;
		*nb += nbr[i] - 48;
		i++;
	}
	return (true);
}

bool	ft_atoi(int *nb, char *nbr)
{
	int	i;

	*nb = 0;
	i = 0;
	while (nbr[i])
	{
		if (*nb > *nb * 10 + nbr[i] - 48)
			return (false);
		*nb *= 10;
		*nb += nbr[i] - 48;
		i++;
	}
	return (true);
}


