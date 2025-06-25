/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:27:22 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/25 15:42:19 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/// @brief Initializer of the project
void	init(t_config *config, char *av[])
{
	config->number_of_philosophers = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	config->simulation_end = 0;
	config->philos_full = 0;
	pthread_mutex_init(&config->full_mutex, NULL);
	if (av[5])
		config->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		config->number_of_times_each_philosopher_must_eat = -1;
}

int	mutex_init(t_config *config)
{
	int	i;

	config->forks = malloc(sizeof(pthread_mutex_t) * \
			config->number_of_philosophers);
	if (!config->forks)
		return (-1);
	i = -1;
	while (++i < config->number_of_philosophers)
	{
		if (pthread_mutex_init(&config->forks[i], NULL) != 0)
			return (-1);
	}
	if (pthread_mutex_init(&config->log, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&config->sim_end_mutex, NULL) != 0)
		return (-1);
	return (0);
}

void	philos_init(t_philo *philos, t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->number_of_philosophers)
	{
		philos[i].idx = i;
		philos[i].is_full = 0;
		philos[i].infoptr = config;
		philos[i].lm_stamp = config->start_time;
		philos[i].meals_eaten = 0;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
	}
}
