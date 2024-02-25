/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:21:36 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/25 22:13:22 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n1;
	int	n2;

	i = 0;
	n1 = 0;
	n2 = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		n2 = n1;
		n1 = (n2 * 10) + (str[i] - 48);
		if (n2 > n1)
			return (-1);
		i++;
	}
	return (n1);
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	unlink_and_close_semaphores(t_data *data)
{
	sem_unlink("fork_semaphore");
	sem_close(data->sem_fork);
	sem_unlink("mssg_semaphore");
	sem_close(data->sem_mssg);
	sem_unlink("last_eat_semaphore");
	sem_close(data->sem_last_eat);
	sem_unlink("count_eat_semaphore");
	sem_close(data->sem_count_eat);
}

void	kill_the_childs(t_data *data)
{
	int	i_dice;

	i_dice = -1;
	while (++i_dice < data->philo_nbr)
		kill(data->process_pid[i_dice], SIGINT);
}

void	*check_is_there_dead(void *data)
{
	t_philo	*p_ilo;

	p_ilo = (t_philo *)data;
	while (p_ilo->data->philo_nbr_eat)
	{
		sem_wait(p_ilo->data->sem_count_eat);
		sem_wait(p_ilo->data->sem_last_eat);
		if (p_ilo->count_eat < p_ilo->data->philo_nbr_eat
			&& get_current_time() - p_ilo->last_eat >= p_ilo->data->philo_die)
		{
			sem_wait(p_ilo->data->sem_mssg);
			printf("\e[1m\e[31m%ld %d died\n\e[0m",
				get_current_time() - p_ilo->data->start_simlt,
				p_ilo->philo_indice);
			sem_post(p_ilo->data->sem_last_eat);
			sem_post(p_ilo->data->sem_count_eat);
			exit(1);
		}
		sem_post(p_ilo->data->sem_last_eat);
		sem_post(p_ilo->data->sem_count_eat);
		usleep(p_ilo->data->philo_eat * 2);
	}
	return (NULL);
}
