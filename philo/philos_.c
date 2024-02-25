/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:17:49 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/25 16:24:55 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_usleep(int time_eat_sleep)
{
	int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_eat_sleep)
		usleep(500);
}

void	philos_print(t_philo *philo, int arg, char *color, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_print_mssg);
	if (!philo->data->print_mssg)
	{
		printf("\e[1m%s%d %d %s\n\e[0m",
			color, get_current_time() - philo->data->start_simlt, arg, str);
	}
	pthread_mutex_unlock(&philo->data->mutex_print_mssg);
}

void	philos_create(t_data *data)
{
	int	i_dice;

	i_dice = -1;
	data->start_simlt = get_current_time();
	while (++i_dice < data->philo_nbr)
		pthread_create(&data->philo_thd[i_dice], NULL,
			philos_simult, &data->philo_data[i_dice]);
	pthread_create(&data->philo_monitor, NULL,
		check_is_there_dead, data);
	pthread_join(data->philo_monitor, NULL);
	i_dice = -1;
	while (++i_dice < data->philo_nbr)
		pthread_join(data->philo_thd[i_dice], NULL);
}

void	*philos_simult(void *philo)
{
	t_philo	*p_ilo;

	p_ilo = (t_philo *)philo;
	pthread_mutex_lock(&p_ilo->data->mutex_eat);
	p_ilo->last_eat = get_current_time();
	pthread_mutex_unlock(&p_ilo->data->mutex_eat);
	if (!(p_ilo->philo_indice % 2))
		philos_usleep(p_ilo->data->philo_eat / 2);
	while (!let_is_check_for_dead(p_ilo->data)
		&& p_ilo->data->philo_nbr_eat)
	{
		if (let_is_think_and_fork(p_ilo))
			break;
		let_is_eat(p_ilo);
		if (p_ilo->data->philo_nbr_eat == p_ilo->count_eat)
			return (NULL);
		let_is_sleep(p_ilo);
	}
	return (NULL);
}
