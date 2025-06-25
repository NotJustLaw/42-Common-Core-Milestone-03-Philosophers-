/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:11:18 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/25 17:46:00 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:11:18 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/25 16:35:00 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_config	cfg;
	t_philo		*philos;
	pthread_t	monitor;
	int			i;

	if (arg_chkr(ac, av) < 0)
		return (1);
	init(&cfg, av);
	philos = malloc(sizeof(*philos) * cfg.number_of_philosophers);
	if (!philos)
		return (1);
	if (mutex_init(&cfg) < 0)
		return (write(2, "Mutex init failed\n", 18), 1);
	cfg.start_time = timestamp_ms();
	philos_init(philos, &cfg);
	if (thread_creation(&cfg, philos) < 0)
		return (free(cfg.forks), free(philos), 1);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < cfg.number_of_philosophers)
		pthread_join(philos[i++].id, NULL);
	cleanup(&cfg, philos);
	return (0);
}
