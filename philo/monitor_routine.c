/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:26:35 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 15:45:26 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_philo *philos, t_config *config)
{
	int		i;
	long	current;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		current = timestamp_ms();
		if (current - philos[i].lm_stamp >= config->time_to_die)
		{
			pthread_mutex_lock(&config->log);
			printf("%ld %ld died\n", current
				- config->start_time, philos[i].idx + 1);
			pthread_mutex_unlock(&config->log);
			pthread_mutex_lock(&config->sim_end_mutex);
			config->simulation_end = 1;
			pthread_mutex_unlock(&config->sim_end_mutex);
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	t_config	*config;

	philos = (t_philo *)arg;
	config = philos[0].infoptr;
	while (!simulation_ended(config))
	{
		if (check_death(philos, config))
			return (NULL);
		pthread_mutex_lock(&config->full_mutex);
		if (config->number_of_times_each_philosopher_must_eat != -1
			&& config->philos_full == config->number_of_philosophers)
		{
			pthread_mutex_lock(&config->sim_end_mutex);
			config->simulation_end = 1;
			pthread_mutex_unlock(&config->sim_end_mutex);
			pthread_mutex_unlock(&config->full_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&config->full_mutex);
		usleep(1000);
	}
	return (NULL);
}
