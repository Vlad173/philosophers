/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:41:48 by pmeredyt          #+#    #+#             */
/*   Updated: 2022/07/13 12:23:09 by pmeredyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(char *str)
{
	int		i;

	i = 0;
	while (*str != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		str++;
	}
	return (0);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}

void	*ft_dead(void *das)
{
	t_philo	*ph;

	ph = (t_philo *)das;
	while (1)
	{
		if (ph->das->tm_to_die < time_get() - ph->life)
		{
			sem_wait(ph->das->sem_wrt);
			printf("%ld %d is died\n", time_get() - ph->das->start_time, \
			ph->ph_id);
			sem_post(ph->das->sem_end);
		}
	}
	return (NULL);
}
