/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:21:43 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 17:54:04 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_single_philo(t_philo *philo)
{
	t_config	*cfg;

	cfg = philo->infoptr;
	pthread_mutex_lock(&cfg->forks[philo->idx]);
	log_action(philo, "has taken a fork");
	while (!simulation_ended(cfg))
		usleep(100);
	pthread_mutex_unlock(&cfg->forks[philo->idx]);
}

void	do_cycle(t_philo *philo, int left, int right)
{
	t_config	*cfg;

	cfg = philo->infoptr;
	pthread_mutex_lock(&cfg->forks[left]);
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(&cfg->forks[right]);
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	update_meals(philo);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (simulation_ended(cfg))
	{
		pthread_mutex_unlock(&cfg->forks[left]);
		pthread_mutex_unlock(&cfg->forks[right]);
		return ;
	}
	log_action(philo, "is eating");
	smart_sleep(cfg->time_to_eat, cfg);
	pthread_mutex_unlock(&cfg->forks[left]);
	pthread_mutex_unlock(&cfg->forks[right]);
	log_action(philo, "is sleeping");
	smart_sleep(cfg->time_to_sleep, cfg);
	log_action(philo, "is thinking");
}

void	update_meals(t_philo *philo)
{
	philo->lm_stamp = timestamp_ms();
	philo->meals_eaten++;
	if (philo->infoptr->number_of_times_each_philosopher_must_eat != -1 && \
		philo->meals_eaten
		== philo->infoptr->number_of_times_each_philosopher_must_eat)
	{
		philo->is_full = 1;
		pthread_mutex_lock(&philo->infoptr->full_mutex);
		philo->infoptr->philos_full++;
		pthread_mutex_unlock(&philo->infoptr->full_mutex);
	}
}
