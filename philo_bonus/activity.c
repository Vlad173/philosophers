/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:41:39 by pmeredyt          #+#    #+#             */
/*   Updated: 2022/07/13 09:28:56 by pmeredyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(char *str, t_philo *ph)
{
	long int	time;

	time = time_get() - ph->das->start_time;
	sem_wait(ph->das->sem_wrt);
	printf("%ld %d %s\n", time, ph->ph_id, str);
	sem_post(ph->das->sem_wrt);
}

void	ft_sleep(int time)
{
	long int	start;

	start = time_get();
	while ((time_get() - start) < (long int)time)
		usleep(100);
}

void	ft_wait(t_data *data)
{
	int			i;
	pthread_t	end;

	pthread_create(&end, NULL, ft_end, data);
	pthread_detach(end);
	sem_wait(data->sem_end);
	i = 0;
	while (i < data->cnt_of_ph)
	{
		kill(data->pids_mas[i], SIGKILL);
		++i;
	}
}

void	*ft_end(void *das)
{
	t_data	*d;
	int		i;

	d = (t_data *)das;
	i = 0;
	while (i < d->cnt_of_ph)
	{
		sem_wait(d->sem_cnt);
		++i;
	}
	sem_post(d->sem_end);
	return (NULL);
}

void	activity(t_philo *ph)
{
	sem_wait(ph->das->sem_frk);
	ft_print("has taken a fork", ph);
	sem_wait(ph->das->sem_frk);
	ft_print("has taken a fork", ph);
	ft_print("is eating", ph);
	++ph->cnt_eat;
	if (ph->cnt_eat == ph->das->must_eat)
		sem_post(ph->das->sem_cnt);
	ph->life = time_get();
	ft_sleep(ph->eat_tm);
	sem_post(ph->das->sem_frk);
	sem_post(ph->das->sem_frk);
	ft_print("is sleeping", ph);
	ft_sleep(ph->slp_tm);
	ft_print("is thinking", ph);
}
