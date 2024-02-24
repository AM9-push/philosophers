/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_init_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:42:52 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/24 16:49:40 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parsing_input(int ac, char *av[])
{
	int	i_dice_1;
	int	i_dice_2;
	int	ac_dice;

	ac_dice = 0;    
	if (ac < 5 || ac > 6)
		return (0);
	while (++ac_dice < ac)
	{
		i_dice_1 = 0;
		i_dice_2 = 0;
		if (av[ac_dice][i_dice_1] == '+') 
			i_dice_1 = ++i_dice_2;
		while (av[ac_dice][i_dice_1])
		{
			if (av[ac_dice][i_dice_2] >= 48 && av[ac_dice][i_dice_2] <= 57)
				i_dice_2++;
			i_dice_1++;
		}
		if (i_dice_1 != i_dice_2)
			return (0);
	}
	return (1);
}

int	init_data(t_data *data, int ac, char *av[])
{
	data->philo_nbr = ft_atoi(av[1]);
	if (data->philo_nbr == -1 || data->philo_nbr > 200)
		return (0);
	data->philo_die = ft_atoi(av[2]);
	if (data->philo_die < 60)
		return (0);
	data->philo_eat = ft_atoi(av[3]);
	if (data->philo_eat < 60)
		return (0);
	data->philo_sleep = ft_atoi(av[4]);
	if (data->philo_sleep < 60)
		return (0);
	if (ac == 6)
	{
		data->philo_nbr_eat = ft_atoi(av[5]);
		if (data->philo_nbr_eat < 0)
			return (0);
	}
	else
		data->philo_nbr_eat = -1;
	return (1);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("fork_semaphore");
	data->sem_fork = sem_open("fork_semaphore", O_CREAT, 0644, data->philo_nbr);
	if (data->sem_fork == SEM_FAILED)
		return (0);
	sem_unlink("mssg_semaphore");
	data->sem_mssg = sem_open("mssg_semaphore", O_CREAT, 0644, 1);
	if (data->sem_mssg == SEM_FAILED)
		return (0);
	sem_unlink("last_eat_semaphore");
	data->sem_last_eat = sem_open("last_eat_semaphore", O_CREAT, 0644, 1);
	if (data->sem_last_eat == SEM_FAILED)
		return (0);
	sem_unlink("count_eat_semaphore");
	data->sem_count_eat = sem_open("count_eat_semaphore", O_CREAT, 0644, 1);
	if (data->sem_count_eat == SEM_FAILED)
		return (0);
	return (1);
}

int	init_philos(t_data *data, int ac)
{
	int	i_dice;

	i_dice = -1;
	while (++i_dice < data->philo_nbr)
	{
		data->philo_data[i_dice].philo_indice = i_dice + 1;
		data->philo_data[i_dice].last_eat = get_current_time();
		if (!data->philo_data[i_dice].last_eat)
			return (0);
		data->philo_data[i_dice].data = data;
		data->philo_data[i_dice].count_eat = -2 * !(ac == 6);
	}
	return (1);
}
