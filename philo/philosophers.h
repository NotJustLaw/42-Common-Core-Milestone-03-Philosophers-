/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:11:29 by justlaw           #+#    #+#             */
/*   Updated: 2025/06/25 17:51:10 by skuhlcke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_config
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				simulation_end;
	int				philos_full;
	pthread_mutex_t	log;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim_end_mutex;
	pthread_mutex_t	full_mutex;
}		t_config;

typedef struct s_philo
{
	int				is_full;
	int				meals_eaten;
	long			idx;
	long			lm_stamp;
	t_config		*infoptr;
	pthread_t		id;
	pthread_mutex_t	meal_mutex;
}		t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				is_taken;
}		t_fork;

//Init
void	init(t_config *config, char *av[]);
int		mutex_init(t_config *config);
void	philos_init(t_philo *philos, t_config *config);

//Philo routine
void	*philo_routine(void *arg);
void	log_action(t_philo *philo, char *action);
int		simulation_ended(t_config *config);
long	timestamp_ms(void);
void	smart_sleep(long duration, t_config *config);

//Routine helpers
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);
int		check_1(t_philo *philo);

//Helpers utils
void	update_meals(t_philo *philo);
void	handle_single_philo(t_philo *philo);
void	do_cycle(t_philo *philo, int left, int right);

// int		try_take_one_fork(t_fork *fork, t_philo *philo);
// void 	release_fork(t_fork *fork);

//Monitor Routine
void	*monitor_routine(void *arg);

//Error
int		arg_chkr(int ac, char *av[]);

//Utils
int		ft_atoi(const char *str);
void	cleanup(t_config *config, t_philo *philos);
int		thread_creation(t_config *config, t_philo *philos);

#endif