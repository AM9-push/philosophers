/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:11:22 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/24 16:48:15 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		philo_thd;
	int				philo_indice;
	int				last_eat;
	int				count_eat;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				philo_die;
	int				philo_eat;
	int				philo_sleep;
	int				philo_nbr_eat;
	long			start_simlt;
	t_philo			philo_data[200];
	pid_t			process_pid[200];
	sem_t			*sem_fork;
	sem_t			*sem_mssg;
	sem_t			*sem_last_eat;
	sem_t			*sem_count_eat;
}			t_data;

int		ft_atoi(const char *str);
int		parsing_input(int ac, char *av[]);
int		init_data(t_data *data, int ac, char *av[]);
int		init_semaphores(t_data *data);
int		init_philos(t_data *data, int ac);
int		get_current_time(void);
void	*check_is_there_dead(void *data);
void	philos_create(t_data *data);

#endif
