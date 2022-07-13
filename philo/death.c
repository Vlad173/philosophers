/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:06:54 by pmeredyt          #+#    #+#             */
/*   Updated: 2022/07/13 12:15:55 by pmeredyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *str)
{
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		str++;
	}
	return (0);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (0);
}

int	check_death_dop(t_data *data, t_philo ph)
{
	if (ph.das->tm_to_die < time_get() - ph.life && ph.life != -14)
	{
		pthread_mutex_lock(&data->write_mutex);
		printf("%ld %d %s\n", time_get() - data->start_time, ph.ph_id, "died");
		return (1);
	}
	return (0);
}

void	*check_death(void	*das)
{
	t_data	*data;
	int		i;

	data = (t_data *)das;
	data->counter = 0;
	while (1)
	{
		i = 0;
		while (i < data->cnt_of_ph)
		{
			if (check_death_dop(data, data->ph[i]))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&data->cnt);
		if (data->counter == data->cnt_of_ph)
		{
			pthread_mutex_lock(&data->write_mutex);
			pthread_mutex_unlock(&data->cnt);
			return (NULL);
		}
		pthread_mutex_unlock(&data->cnt);
	}
	return (NULL);
}

int	ft_death(t_data *data)
{
	pthread_t	death;
	int			i;

	i = 0;
	if (pthread_create(&death, NULL, check_death, data))
		return (ft_error("Error\nPthread create error"));
	pthread_join(death, NULL);
	while (i < data->cnt_of_ph)
	{
		pthread_mutex_destroy(&data->ph->l_f);
		++i;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->cnt);
	free(data->ph);
	return (0);
}
