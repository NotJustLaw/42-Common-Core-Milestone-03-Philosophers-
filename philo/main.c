/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:11:18 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/25 15:42:36 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char *av[])
{
	t_config	config;
	t_philo		*philos;
	pthread_t	monitor;
	int			i;

	if (arg_chkr(ac, av) < 0)
		return (1);
	init(&config, av);
	philos = malloc(sizeof(t_philo) * config.number_of_philosophers);
	if (!philos)
		return (1);
	if (mutex_init(&config) < 0)
		return (write(2, "Mutex init failed\n", 18), -1);
	config.start_time = timestamp_ms();
	philos_init(philos, &config);
	if (thread_creation(&config, philos) < 0)
		return (free(config.forks), 1);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < config.number_of_philosophers)
		pthread_join(philos[i++].id, NULL);
	cleanup(&config, philos);
	return (0);
}
