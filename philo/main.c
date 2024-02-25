/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:05:31 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/25 16:00:59 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data->i_m_dead = 0;
	data->print_mssg = 0;
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i_dice;

	i_dice = -1;
	while (++i_dice < data->philo_nbr)
		if (pthread_mutex_init(&data->m_tex[i_dice], NULL))
			return (0);
	if (pthread_mutex_init(&data->mutex_fork, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_eat, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_count_eat, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_print_mssg, NULL))
		return (0);
	return (1);
}

int	init_philos(t_data *data, int ac)
{
	int	i_dice;

	i_dice = -1;
	while (++i_dice < data->philo_nbr)
	{
		data->philo_data[i_dice].data = data;
		data->philo_data[i_dice].left_fork = &data->m_tex[i_dice];
		if (i_dice == data->philo_nbr - 1)
			data->philo_data[i_dice].right_fork = &data->m_tex[0];
		else
			data->philo_data[i_dice].right_fork = &data->m_tex[i_dice + 1];
		data->start_simlt = get_current_time();
		if (!data->start_simlt)
			return (0);
		data->philo_data[i_dice].philo_indice = i_dice + 1;
		data->philo_data[i_dice].count_eat = -2 * !(ac == 6);
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (parsing_input(ac, av) && init_data(&data, ac, av)
		&& init_mutex(&data) && init_philos(&data, ac))
	{
		philos_create(&data);
		destroy_mutex(&data);
	}
	else
		return (write(2, "\e[1m\e[91mINPUT ERROR\n\e[0m", 21), 1);
	return (0);
}
