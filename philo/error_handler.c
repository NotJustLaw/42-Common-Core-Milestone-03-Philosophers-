/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:37 by skuhlcke          #+#    #+#             */
/*   Updated: 2025/06/25 17:46:38 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_number(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	arg_chkr(int ac, char *av[])
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		write(2,
			"Usage: ./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n", 123);
		return (-1);
	}
	i = 0;
	while (++i < ac)
	{
		if (!is_number(av[i]))
		{
			printf("Error: argument %d ('%s') is not a positive integer\n",
				i, av[i]);
			return (-1);
		}
	}
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1
		|| ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1
		|| (ac == 6 && ft_atoi(av[5]) < 1))
		return (printf("Error: all arguments must be greater than zero\n"), -1);
	return (0);
}
