/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:17:49 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/25 18:21:01 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philos_usleep(int time_eat_sleep)
{
	int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_eat_sleep)
		usleep(500);
}

void	philos_print(t_philo *philo, int arg, char *color, char *str)
{
	sem_wait(philo->data->sem_mssg);
	printf("\e[1m%s%ld %d %s\n\e[0m",
		color, get_current_time() - philo->data->start_simlt, arg, str);
	sem_post(philo->data->sem_mssg);
}

void	philos_last_and_count_eat(t_philo *philo)
{
	sem_wait(philo->data->sem_count_eat);
	philo->count_eat += (philo->count_eat != -2);
	sem_post(philo->data->sem_count_eat);
	sem_wait(philo->data->sem_count_eat);
	philo->last_eat = get_current_time();
	sem_post(philo->data->sem_count_eat);
}

void	philos_simult(t_philo *philo)
{
	pthread_create(&philo->philo_thd, NULL, check_is_there_dead, philo);
	pthread_detach(philo->philo_thd);
	while (philo->data->philo_nbr_eat)
	{
		sem_wait(philo->data->sem_fork);
		philos_print(philo, philo->philo_indice, "\e[93m", "has taken a fork");
		if (philo->data->philo_nbr == 1)
			philos_usleep(philo->data->philo_die * 2);
		sem_wait(philo->data->sem_fork);
		philos_print(philo, philo->philo_indice, "\e[93m", "has taken a fork");
		philos_print(philo, philo->philo_indice, "\e[92m", "is eating");
		philos_last_and_count_eat(philo);
		philos_usleep(philo->data->philo_eat);
		sem_post(philo->data->sem_fork);
		sem_post(philo->data->sem_fork);
		if (philo->count_eat == philo->data->philo_nbr_eat)
			exit(0);
		philos_print(philo, philo->philo_indice, "\e[90m", "is sleeping");
		philos_usleep(philo->data->philo_sleep);
		philos_print(philo, philo->philo_indice, "\e[96m", "is thinking");
	}
	exit(0);
}

void	philos_create(t_data *data)
{
	int	i_dice;

	data->start_simlt = get_current_time();
	i_dice = -1;
	while (++i_dice < data->philo_nbr)
	{
		data->process_pid[i_dice] = fork();
		if (!data->process_pid[i_dice])
			philos_simult(&data->philo_data[i_dice]);
	}
	i_dice = -1;
	while (++i_dice < data->philo_nbr)
		waitpid(-1, 0, 0);
}
