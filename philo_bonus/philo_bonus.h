/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:42:41 by pmeredyt          #+#    #+#             */
/*   Updated: 2022/07/13 11:11:07 by pmeredyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					cnt_of_ph;
	int					tm_to_die;
	int					tm_to_eat;
	int					tm_to_sleep;
	int					must_eat;
	t_philo				*ph;
	long int			start_time;
	pid_t				*pids_mas;
	sem_t				*sem_frk;
	sem_t				*sem_wrt;
	sem_t				*sem_end;
	sem_t				*sem_cnt;
}						t_data;

typedef struct s_philo
{
	int					ph_id;
	int					eat_tm;
	int					slp_tm;
	int					cnt_eat;
	long int			life;
	t_data				*das;
	pthread_t			thread;
	pid_t				pid;
}						t_philo;

long int	time_get(void);
void		ft_sleep(int time);
void		*ft_dead(void *das);
int			ft_error(char *str);
void		activity(t_philo *ph);
int			check_args(char *str);
void		ft_wait(t_data *data);
int			philo_make(t_data *data);
int			ft_atoi(const char *str);
void		*philosophing(void	*das);
int			ft_shield(long i, long a);
int			ft_life(t_data *data, int i);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_print(char *str, t_philo *ph);
void		init_philo(t_data *data, int ind);
int			args_pars(int argc, char **argv, t_data *data);
void		*ft_end(void *das);

#endif
