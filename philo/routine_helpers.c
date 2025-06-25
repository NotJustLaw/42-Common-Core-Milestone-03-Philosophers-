/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:08:06 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 14:24:25 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_1(t_philo *philo)
{
	int	left;

	if (philo->infoptr->number_of_philosophers != 1)
		return (0);
	left = philo->idx;
	pthread_mutex_lock(&philo->infoptr->forks[left]);
	log_action(philo, "has taken a fork");
	while (!simulation_ended(philo->infoptr))
		usleep(100);
	pthread_mutex_unlock(&philo->infoptr->forks[left]);
	return (1);
}

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->idx;
	right = (philo->idx + 1) % philo->infoptr->number_of_philosophers;
	if (simulation_ended(philo->infoptr) || check_1(philo))
		return ;
	if (philo->idx % 2 == 0)
		take_forks_even(philo, left, right);
	else
		take_forks_odd(philo, left, right);
	if (simulation_ended(philo->infoptr))
	{
		pthread_mutex_unlock(&philo->infoptr->forks[left]);
		pthread_mutex_unlock(&philo->infoptr->forks[right]);
	}
}

void	eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->idx;
	right = (philo->idx + 1) % philo->infoptr->number_of_philosophers;
	if (simulation_ended(philo->infoptr))
		return ;
	pthread_mutex_lock(&philo->meal_mutex);
	update_meals(philo);
	log_action(philo, "is eating");
	smart_sleep(philo->infoptr->time_to_eat, philo->infoptr);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!simulation_ended(philo->infoptr))
	{
		pthread_mutex_unlock(&philo->infoptr->forks[left]);
		pthread_mutex_unlock(&philo->infoptr->forks[right]);
	}
}

void	sleep_and_think(t_philo *philo)
{
	if (simulation_ended(philo->infoptr))
		return ;
	log_action(philo, "is sleeping");
	smart_sleep(philo->infoptr->time_to_sleep, philo->infoptr);
	if (simulation_ended(philo->infoptr))
		return ;
	log_action(philo, "is thinking");
}
