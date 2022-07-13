/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:41:51 by pmeredyt          #+#    #+#             */
/*   Updated: 2022/07/13 12:25:03 by pmeredyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_data *data, int ind)
{
	data->ph[ind].das = data;
	data->ph[ind].eat_tm = data->tm_to_eat;
	data->ph[ind].slp_tm = data->tm_to_sleep;
	data->ph[ind].ph_id = ind + 1;
	data->ph[ind].cnt_eat = 0;
	data->ph[ind].life = time_get();
}

int	ft_life(t_data *data, int i)
{
	pthread_t	ded;

	data->pids_mas[i] = fork();
	if (data->pids_mas[i] < 0)
	{
		write(2, "bad fork\n", 9);
		exit(0);
	}
	if (data->pids_mas[i] == 0)
	{
		if (i % 2)
			ft_sleep(10);
		pthread_create(&ded, NULL, ft_dead, &data->ph[i]);
		pthread_detach(ded);
		while (1)
			activity(&data->ph[i]);
		exit(0);
	}
	return (0);
}

int	philo_make(t_data *data)
{
	int			i;

	i = 0;
	data->pids_mas = (pid_t *) malloc(sizeof(pid_t) * data->cnt_of_ph);
	if (!data->pids_mas)
		return (ft_error("Not malloced"));
	data->ph = (t_philo *) malloc(sizeof(t_philo) * data->cnt_of_ph);
	if (!data->ph)
		return (ft_error("Not malloced"));
	sem_unlink("/sema");
	sem_unlink("/print");
	sem_unlink("/end");
	sem_unlink("/count");
	data->sem_frk = sem_open("/sema", O_CREAT, 666, data->cnt_of_ph);
	data->sem_wrt = sem_open("/print", O_CREAT, 666, 1);
	data->sem_end = sem_open("/end", O_CREAT, 666, 0);
	data->sem_cnt = sem_open("/count", O_CREAT, 666, 0);
	while (i < data->cnt_of_ph)
	{
		init_philo(data, i);
		ft_life(data, i);
		++i;
	}
	ft_wait(data);
	return (0);
}

int	args_pars(int argc, char **argv, t_data *data)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if ((check_args(argv[i])) != 0)
			return (-1);
		i++;
	}
	data->cnt_of_ph = ft_atoi(argv[1]);
	data->tm_to_die = ft_atoi(argv[2]);
	data->tm_to_eat = ft_atoi(argv[3]);
	data->tm_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat == 0)
			exit(0);
	}
	else
		data->must_eat = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Not malloced"));
	if (argc >= 5 && argc <= 6)
	{
		data->start_time = time_get();
		if (args_pars(argc, argv, data))
			return (ft_error("Error\nInvalid parameters\n"));
		philo_make(data);
	}
	else
		return (ft_error("Error\nCheck Arguments\n"));
	free(data->pids_mas);
	free(data->ph);
	free(data);
	return (0);
}
