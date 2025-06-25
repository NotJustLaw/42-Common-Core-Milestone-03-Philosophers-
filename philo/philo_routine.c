/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:48:27 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 17:52:49 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(long duration, t_config *config)
{
	long	start;
	long	now;

	start = timestamp_ms();
	while (!simulation_ended(config))
	{
		now = timestamp_ms();
		if (now - start >= duration)
			break ;
		usleep(100);
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
	t_philo		*philo;
	t_config	*cfg;
	int			left;
	int			right;

	philo = arg;
	cfg = philo->infoptr;
	left = philo->idx;
	right = (left + 1) % cfg->number_of_philosophers;
	if (cfg->number_of_philosophers == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if ((left % 2) == 0)
		usleep(cfg->time_to_eat * 1000);
	while (!simulation_ended(cfg))
		do_cycle(philo, left, right);
	return (NULL);
}
