/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:08:06 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 17:53:29 by skuhlcke         ###   ########.fr       */
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
