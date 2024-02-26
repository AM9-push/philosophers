/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:10:43 by aachalla          #+#    #+#             */
/*   Updated: 2024/02/26 21:16:45 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	t_data	data;

	if (parsing_input(ac, av) && init_data(&data, ac, av)
		&& init_philos(&data, ac) && init_semaphores(&data))
		philos_create(&data);
	else
		return (write(2, "\e[1m\e[91mINPUT ERROR\n\e[0m", 21), 1);
	return (0);
}
