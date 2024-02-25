/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_is_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:42:52 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/25 16:39:11 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	let_is_check_for_dead(t_data *data)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->i_m_dead)
		return (pthread_mutex_unlock(&data->mutex_dead), 0);
	return (pthread_mutex_unlock(&data->mutex_dead), 1);
}

int	let_is_think_and_fork(t_philo *philo)
{
	philos_print(philo, philo->philo_indice, "\e[96m", "is thinking");
	pthread_mutex_lock(philo->right_fork);
	philos_print(philo, philo->philo_indice, "\e[93m", "has taken a fork");
	if (philo->data->philo_nbr == 1)
		return (pthread_mutex_unlock(philo->right_fork), 1);
	pthread_mutex_lock(philo->left_fork);
	philos_print(philo, philo->philo_indice, "\e[93m", "has taken a fork");
	return (0);
}

void	let_is_eat(t_philo *philo)
{
	philos_print(philo, philo->philo_indice, "\e[92m", "is eating");
	pthread_mutex_lock(&philo->data->mutex_count_eat);
	philo->count_eat += (philo->count_eat != -2);
	pthread_mutex_unlock(&philo->data->mutex_count_eat);
	pthread_mutex_lock(&philo->data->mutex_eat);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->data->mutex_eat);
	philos_usleep(philo->data->philo_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	let_is_sleep(t_philo *philo)
{
	philos_print(philo, philo->philo_indice, "\e[90m", "is sleeping");
	philos_usleep(philo->data->philo_sleep);
}

void	let_is_finish_him(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_eat);
	pthread_mutex_unlock(&philo->data->mutex_count_eat);
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->data->i_m_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_print_mssg);
	philo->data->print_mssg = 1;
	pthread_mutex_unlock(&philo->data->mutex_print_mssg);
	printf("\e[1m\e[31m%d %d died\n\e[0m", get_current_time()
		- philo->data->start_simlt,
		philo->philo_indice);
}
