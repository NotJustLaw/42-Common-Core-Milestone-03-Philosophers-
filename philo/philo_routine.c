/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:48:27 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 15:47:15 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(long duration, t_config *config)
{
	long	start;

	start = timestamp_ms();
	while (!simulation_ended(config))
	{
		if (timestamp_ms() - start >= duration)
			break ;
		usleep(50);
	}
}

void	log_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->infoptr->log);
	if (simulation_ended(philo->infoptr))
	{
		pthread_mutex_unlock(&philo->infoptr->log);
		return ;
	}
	timestamp = timestamp_ms() - philo->infoptr->start_time;
	printf("%ld %ld %s\n", timestamp, philo->idx + 1, action);
	pthread_mutex_unlock(&philo->infoptr->log);
}

int	simulation_ended(t_config *config)
{
	int	ended;

	pthread_mutex_lock(&config->sim_end_mutex);
	ended = config->simulation_end;
	pthread_mutex_unlock(&config->sim_end_mutex);
	return (ended);
}

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->lm_stamp = timestamp_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (check_1(philo))
		return (NULL);
	if (philo->idx % 2 == 0)
		usleep(200);
	while (!simulation_ended(philo->infoptr))
	{
		take_forks(philo);
		if (simulation_ended(philo->infoptr))
			break ;
		eat(philo);
		if (simulation_ended(philo->infoptr))
			break ;
		sleep_and_think(philo);
		if (simulation_ended(philo->infoptr))
			break ;
		usleep(100);
	}
	return (NULL);
}
