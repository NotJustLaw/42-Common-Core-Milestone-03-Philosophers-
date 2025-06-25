/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:15:50 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/25 17:11:35 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	cleanup(t_config *config, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_destroy(&config->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&config->log);
	pthread_mutex_destroy(&config->sim_end_mutex);
	pthread_mutex_destroy(&config->full_mutex);
	free(config->forks);
	free(philos);
}

int	thread_creation(t_config *config, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < config->number_of_philosophers)
	{
		if (pthread_create(&philos[i].id, NULL, philo_routine, &philos[i]) != 0)
			return (write(2, "Thread creation failed\n", 24), -1);
		usleep(100);
	}
	return (0);
}
