/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:21:36 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/24 03:28:41 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_count_eat(t_data *data)
{
	int	i_dice;
	int	count_eat;

	i_dice = -1;
	count_eat = 0;
	pthread_mutex_lock(&data->mutex_count_eat);
	while (++i_dice < data->philo_nbr)
	{
		if (data->philo_data[i_dice].count_eat != -1)
			if (data->philo_data[i_dice].count_eat
				>= data->philo_data[i_dice].data->philo_nbr_eat)
				count_eat++;
	}
	if (count_eat == data->philo_nbr)
		return (pthread_mutex_unlock(&data->mutex_count_eat),
			1);
	return (pthread_mutex_unlock(&data->mutex_count_eat),
		0);
}

void	destroy_mutex(t_data *data)
{
	int	i_dice;

	i_dice = -1;
	while (++i_dice)
		pthread_mutex_destroy(&data->m_tex[i_dice]);
	pthread_mutex_destroy(&data->mutex_fork);
	pthread_mutex_destroy(&data->mutex_eat);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_bye);
	pthread_mutex_destroy(&data->mutex_count_eat);
}

void	*check_is_there_dead(void *d_ta)
{
	t_data	*data;
	int		i_dice;

	data = (t_data *)d_ta;
	if (!data->philo_nbr)
		return (NULL);
	while (4)
	{
		i_dice = -1;
		while (++i_dice < data->philo_nbr)
		{
			pthread_mutex_lock(&data->mutex_eat);
			pthread_mutex_lock(&data->mutex_count_eat);
			if (data->philo_data[i_dice].count_eat < data->philo_nbr_eat
				&& get_current_time() - data->philo_data[i_dice].last_eat
				>= data->philo_data[i_dice].data->philo_die)
				return (let_is_finish_him(&data->philo_data[i_dice]),
					NULL);
			pthread_mutex_unlock(&data->mutex_eat);
			pthread_mutex_unlock(&data->mutex_count_eat);
			if (ft_count_eat(data))
				return (NULL);
			usleep(1000);
		}
	}
}
