/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:06:41 by pmeredyt          #+#    #+#             */
/*   Updated: 2022/07/13 11:25:27 by pmeredyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *str, t_philo *ph)
{
	long int	time;

	time = time_get() - ph->das->start_time;
	pthread_mutex_lock(&ph->das->write_mutex);
	printf("%ld %d %s\n", time, ph->ph_id, str);
	pthread_mutex_unlock(&ph->das->write_mutex);
}

void	ft_sleep(int time)
{
	long int	start;

	start = time_get();
	while ((time_get() - start) < (long int)time)
		usleep(100);
}

void	sleeping(t_philo *ph)
{
	ft_print("is sleeping", ph);
	ft_sleep(ph->slp_tm);
}

void	eating(t_philo *ph)
{
	ft_print("is eating", ph);
	ph->life = time_get();
	ft_sleep(ph->eat_tm);
	pthread_mutex_lock(&ph->das->cnt);
	++ph->cnt_eat;
	if (ph->cnt_eat == ph->das->must_eat)
		++ph->das->counter;
	pthread_mutex_unlock(&ph->das->cnt);
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_unlock(ph->r_f);
}

void	forking(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	ft_print("has taken fork", ph);
	pthread_mutex_lock(ph->r_f);
	ft_print("has taken fork", ph);
}
