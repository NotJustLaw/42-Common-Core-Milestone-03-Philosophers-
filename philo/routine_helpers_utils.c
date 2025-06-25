/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:21:43 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 15:46:16 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	try_lock_fork(t_philo *philo, int fork_idx)
{
	while (!simulation_ended(philo->infoptr))
	{
		if (pthread_mutex_trylock(&philo->infoptr->forks[fork_idx]) == 0)
		{
			log_action(philo, "has taken a fork");
			return (1);
		}
		usleep(50);
	}
	return (0);
}

void	take_forks_even(t_philo *philo, int left, int right)
{
	if (!try_lock_fork(philo, right))
		return ;
	if (!try_lock_fork(philo, left))
		pthread_mutex_unlock(&philo->infoptr->forks[right]);
}

void	take_forks_odd(t_philo *philo, int left, int right)
{
	if (!try_lock_fork(philo, left))
		return ;
	if (!try_lock_fork(philo, right))
		pthread_mutex_unlock(&philo->infoptr->forks[left]);
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
