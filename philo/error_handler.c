/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:37 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 15:44:18 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	arg_chkr(int ac, char *av[])
{
	int	nop;

	if (ac != 5 && ac != 6)
	{
		write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 123);
		return (-1);
	}
	nop = ft_atoi(av[1]);
	if (nop <= 0)
		return (printf("Please put 1 or more philos, not less\n"), -1);
	return (0);
}
