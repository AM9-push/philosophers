/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:05:16 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/25 18:10:15 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				philo_indice;
	int				last_eat;
	int				count_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				philo_die;
	int				philo_eat;
	int				philo_sleep;
	int				philo_nbr_eat;
	int				start_simlt;
	int				i_m_dead;
	int				print_mssg;
	t_philo			philo_data[200];
	pthread_t		philo_thd[200];	
	pthread_t		philo_monitor;	
	pthread_mutex_t	m_tex[200];
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_count_eat;
	pthread_mutex_t	mutex_print_mssg;
}				t_data;

int		ft_atoi(const char *str);
int		get_current_time(void);
void	philos_usleep(int time_eat_sleep);
void	philos_print(t_philo *philo, int arg, char *color, char *str);
void	philos_create(t_data *data);
void	*philos_simult(void *philo);
void	*check_is_there_dead(void *d_ta);
int		let_is_fork(t_philo *philo);
int		let_is_check_for_dead(t_data *data);
void	let_is_finish_him(t_philo *philo);
void	let_is_eat(t_philo *philo);
void	let_is_sleep_and_think(t_philo *philo);
void	destroy_mutex(t_data *data);

#endif
